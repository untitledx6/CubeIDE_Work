/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "pid.h" //pid运算头文件
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define Sample_Num 100 //每一个通道的采样数
#define Channel_Num  2//通道数量， 一个为电压量，一个为电流量。
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t ADC_ConvertedValue[Sample_Num][Channel_Num]; //定义DMA数据的存储地址
float ADC_Valuetmp[Sample_Num][Channel_Num]; //DMA数据的缓冲区
float ADC_ValueAverage[Channel_Num]; //用于存储滤波处理之后的数据
uint16_t DMA_Data_Ready_Flag = 0; //DMA数据就绪标志，为1表示数据已移至缓冲区，为0表示等待数据采集。
float Target_V = 1; //设置目标电压值
float Max_I = 1; //设置最大电流(为AD采样前 电流转换后 的模拟电压值)
uint16_t Pwm_Reload_Value = 1000; //pwm自动重装值
uint16_t Pwm_Compare_Value = 700; //pwm比较值 二者之比即为占空比
uint16_t Up_Button_Num = 0; //定时器消抖所需的临时变量
uint16_t Down_Button_Num = 0;
uint16_t Up_Button_Flag = 0; //升压按钮按下的标志
uint16_t Down_Button_Flag = 0; //降压按钮按下的标志
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADC_ConvertedValue, Sample_Num * Channel_Num); //开启ADC的DMA采集通道
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1); //开启PWM输出，重装值为1000，比较值为700
  //__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, n);通过此函数调节占空比
  Set_PID_Parameter(KP,KI,KD); //PID调节参数

  HAL_TIM_Base_Start_IT(&htim3); //开启定时器3中断，10ms
  HAL_TIM_Base_Start_IT(&htim4);//开启定时器4中断，10ms

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(Up_Button_Flag != 0) { //如果升压按键被按下
		  Target_V += 0.05; //目标电压增加
		  Up_Button_Flag = 0; //标志位清零
	  }
	  if(Down_Button_Flag != 0) { //如果降压按键被按下
	 		  Target_V -= 0.05; //目标电压减小
	 		  Down_Button_Flag = 0; //标志位清零
	  }
	  if(DMA_Data_Ready_Flag == 1) { //数据已到达缓冲区，进行数据处理
	  		  //首先对数据的每一列做排序
	  		  for(int l=0; l<Channel_Num; l++) {
	  			  for(int i=0; i<Sample_Num-1; i++) { // 冒泡排序
	  				  for(int j=0; j<Sample_Num-i; j++) {
	  					  if(ADC_Valuetmp[j][l] > ADC_Valuetmp[j+1][l]) {
	  						  float tmp = ADC_Valuetmp[j][l];
	  						  ADC_Valuetmp[j][l] = ADC_Valuetmp[j+1][l];
	  						  ADC_Valuetmp[j+1][l] = tmp;
	  					  }
	  				  }
	  			  }
	  		  }
	  		  //然后取排序后中间部分的值求和平均滤波
	  		  for(int l=0; l<Channel_Num; l++) {
	  			  float Sum = 0;
	  			  for(int i=Sample_Num/2-25; i<Sample_Num/2+25; i++) {	//取中间值算平均值
	  				  Sum += ADC_Valuetmp[i][l];
	  			  }
	  			  ADC_ValueAverage[l] = Sum/50;
	  		  }

	  		  if(ADC_ValueAverage[1] < Max_I) { //如果采集到的电流值小于最大电流，则保持恒压状态
	  			  float Pid_Output = PID_Calc(ADC_ValueAverage[0], Target_V); //进行Pid运算
	  			  Pwm_Compare_Value += (uint16_t) Pid_Output; //pwm比较值加上pid运算结果，实现闭环控制
	  			  if(Pwm_Compare_Value >= Pwm_Reload_Value) {//如果占空比大于1则，回调为1/2
	  				  Pwm_Compare_Value = Pwm_Reload_Value/2;
	  			  }
	  			  if(Pwm_Compare_Value <= 0) { //如果占空比小于0则调为0
	  				  Pwm_Compare_Value = 0;
	  			  }
	  			  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Pwm_Compare_Value); //进行占空比调整
	  		  }

	  		  if(ADC_ValueAverage[1] >= Max_I) { //如果采集到的电流值大于最大电流,则使电路停止输出
	  			  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 2); //占空比调低
	  			  while(1); //进入死循环，等待重启系统
	  		  }
	  		/*
	  				  if(ADC_ValueAverage[1] >= Max_I) { //如果采集到的电流值大于最大电流，则转为恒流状态
	  					  float Pid_Output = PID_Calc(ADC_ValueAverage[1], Max_I); //进行Pid运算
	  					  Pwm_Compare_Value += (uint16_t) Pid_Output; //pwm比较值加上pid运算结果，实现闭环控制
	  					  if(Pwm_Compare_Value >= Pwm_Reload_Value) {//如果占空比大于1则，回调为1/2
	  						  Pwm_Compare_Value = Pwm_Reload_Value/2;
	  					  }
	  					  if(Pwm_Compare_Value <= 0) { //如果占空比小于0则调为0
	  						  Pwm_Compare_Value = 0;
	  					  }
	  					  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Pwm_Compare_Value); //进行占空比调整
	  				  }
	  				  */


		  DMA_Data_Ready_Flag = 0; //准备下一轮采样
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/*此函数为DMA一轮采集数据完成后的DMA中断*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {

	if(DMA_Data_Ready_Flag == 0) { //主函数处于等待数据采集状态时。
		/*将采集的数据移动到缓冲区*/
		for(int x = 0; x < Sample_Num; x++) {
			for(int y = 0; y < Channel_Num; y++) {
				ADC_Valuetmp[x][y] = (float)ADC_ConvertedValue[x][y] / 4096 * 3.3;
			}
		}
		DMA_Data_Ready_Flag = 1; //将标志置1，告诉主函数对缓冲区中的数据做处理。
	}
	else {
		//主函数未处理完数据，采集到的数据丢弃。
	}

}

//定时中断函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if(htim->Instance == htim3.Instance) { //如果是定时器3的中断
		if(HAL_GPIO_ReadPin(Up_Button_GPIO_Port, Up_Button_Pin) == GPIO_PIN_RESET) { //按键被按下
			Up_Button_Num++;//按键按下的时间为Down_Button_Num*10ms
		}
		if(Up_Button_Num >= 10 && HAL_GPIO_ReadPin(Up_Button_GPIO_Port, Up_Button_Pin) == GPIO_PIN_SET) {//如果按下超过100ms并且以及松开
			Up_Button_Flag++;//则认为为有效的按键操作
			Up_Button_Num = 0;//清零，准备下一次按下
		}
	}

	if(htim->Instance == htim4.Instance) { //如果是定时器4的中断
			if(HAL_GPIO_ReadPin(Down_Button_GPIO_Port, Down_Button_Pin) == GPIO_PIN_RESET) { //按键被按下
				Down_Button_Num++; //按键按下的时间为Down_Button_Num*10ms
			}
			if(num >= 10 && HAL_GPIO_ReadPin(Down_Button_GPIO_Port, Down_Button_Pin) == GPIO_PIN_SET) { //如果按下超过100ms并且以及松开
				Down_Button_Flag++; //则认为为有效的按键操作
				Down_Button_Num = 0; //清零，准备下一次按下
			}
		}

}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
