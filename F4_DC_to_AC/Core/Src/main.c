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
#include "math.h"
#include "pid.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define Channel_Num  2//通道数量， 一个为电压量，一个为电流量。
#define SIN_NUM 50 //函数sin表数组的容量
#define Cycle_Num 200 //tim7为0.1ms一次采样，输出一个周期20ms。所以一个周期应该有200个采样值
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t ADC_ConvertedValue[Channel_Num] = {0}; //定义DMA数据的存储地址
int SIN_LUT_index = 0;//sin表指针，用来定位sin表中的值
uint16_t Sin_Lut[SIN_NUM] = {0};  //sin表
uint16_t Output_Polarity_Flag = 0; //输出极性标志，0和1分别为前半周期和后半周期
float Tfb = 1; //输出的调幅比
uint16_t Get_Data_Cycle_Flag = 0; //获取一个周期数据的标志
float ADC_Cycle_Date[Cycle_Num][Channel_Num] = {0}; // 存放一个周期的电流电压值
uint16_t ADC_Date_Count = 0; //周期内ADC采样值计数
float ADC_ValueAverage[Channel_Num] = {0}; //存储经main函数运算之后的电压电流有效值
float Target_V = 1; //设置目标电压值
float Max_I = 1; //设置最大电流(为AD采样前 电流转换后 的模拟电压值)
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Make_Sin_List(void); //sin表生成函数
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
  MX_TIM2_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADC_ConvertedValue, Channel_Num); //开启ADC的DMA采集通道
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1); //开启PWM通道1输出，控制boost的占空比
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 3000);//设置初值，重装值为8400
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2); //开启PWM通道2输出，控制一个桥臂
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 4200);//设置初值，重装值为8400
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3); //开启PWM通道3输出，控制另外一个桥臂
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 4200);//设置初值，重装值为8400
  Make_Sin_List(); //生成正弦表
  HAL_TIM_Base_Start_IT(&htim2); //开启定时器2，中断中输出正弦调制波
  HAL_TIM_Base_Start_IT(&htim7); //开启定时器7，中断中进行数据采样和 闭环控制
  Set_PID_Parameter(kp,ki,kd); //PID参数配置
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(Get_Data_Cycle_Flag == 1) { //标志为1 对一个周期的数据计算处理

		  float SumV = 0, SumI = 0; //存储总值
		  float I_Diff = 2.1; //电流用INA282可采到负值，但有偏置，计算时应减去
		  for(int i = 0; i < Cycle_Num; i++) { //做平方求和
			  SumV += ADC_Cycle_Date[i][0] * ADC_Cycle_Date[i][0];
			  SumI += (ADC_Cycle_Date[i][1] - I_Diff) * (ADC_Cycle_Date[i][1] - I_Diff);
		  }
		  ADC_ValueAverage[0] = sqrt(SumV * 2 / Cycle_Num); //电压有效值  在负半周采样结果为0，故乘2
		  ADC_ValueAverage[1] = sqrt(SumI / Cycle_Num); //电流有效值

		  if(ADC_ValueAverage[1] < Max_I) { //如果采集到的电流值小于最大电流，则保持恒压状态
			  float Pid_Output = PID_Calc(ADC_ValueAverage[0], Target_V); //进行Pid运算
			  float Tfb_Temp = Tfb; //调幅比临时存储变量
			  Tfb_Temp += Pid_Output; //调幅比加上pid运算结果，实现闭环控制
			  if(Tfb_Temp > 1) {//如果调幅比大于1则，回调为1
				  Tfb_Temp = 1;
			  }
			  if(Tfb_Temp < 0) { //如果调幅比小于0则调为0
				  Tfb_Temp = 0;
			  }
			  Tfb = Tfb_Temp; //进行调幅比调整
		  }
		  if(ADC_ValueAverage[1] >= Max_I) { //如果采集到的电流值大于最大电流,则使电路停止输出
			  Tfb = 0; //调幅比调低
			  while(1); //进入死循环，等待重启系统
		  }

		  Get_Data_Cycle_Flag = 0;
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

void Make_Sin_List(void) {//生成sin表的函数
	uint16_t i;
	for(i = 0; i < SIN_NUM; i++) {
		Sin_Lut[i] = (uint16_t)(sin(3.1415926*i/SIN_NUM)*(8400-1));//8400为pwm的定时器重装值
	}
}

		/*定时器中断函数*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if(htim->Instance == htim2.Instance) {  //调制定时器2中断处理
		if(Output_Polarity_Flag == 0) {		//标志为0
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);	//定时器1的通道2	一个桥臂，使其停止工作
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, Tfb*Sin_Lut[SIN_LUT_index]); //定时器1的通道3，另一个桥臂输出PWM
		} else {	 //标志不为0
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);	//定时器1的通道3	一个桥臂，使其停止工作
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, Tfb*Sin_Lut[SIN_LUT_index]); //定时器1的通道2，另一个桥臂输出PWM
		}
		SIN_LUT_index++;  //表指针+1
		if( SIN_LUT_index == SIN_NUM ) { //sin半周期转换桥臂
			SIN_LUT_index = 0;           //正弦表指针归零
			Output_Polarity_Flag = ~Output_Polarity_Flag; //转换桥臂标志
		}
	}

	if(htim->Instance == htim7.Instance) {  //采样定时器7中断处理
		if(!Get_Data_Cycle_Flag) { //标志为0应该去获取一个周期的数据
			if(ADC_Date_Count < 200) {	// 记录一个周期内ADC采样值
				ADC_Cycle_Date[ADC_Date_Count][0] = (float)ADC_ConvertedValue[0]/4096*3.3; //移动存储以交给main函数处理
				ADC_Cycle_Date[ADC_Date_Count][1] = (float)ADC_ConvertedValue[1]/4096*3.3;
				ADC_Date_Count++;
			}else if(ADC_Date_Count >= 200) { //一个周期记录完成
				ADC_Date_Count = 0; //计数值清零
				Get_Data_Cycle_Flag = 1; //标志拉高交给main函数处理
			}
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
