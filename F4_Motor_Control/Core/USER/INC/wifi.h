/*
具体内容 参照这两篇教程

https://blog.csdn.net/HelloXiaoYueYue/article/details/44941811

https://www.shaoguoji.cn/2017/01/15/ESP8266-usage/

*/

//教程
/*
开UART1 和其中断
重定向printf
首先 include"wifi.h"
使用Server_Init();
  HAL_Delay(500);
  HAL_UART_Receive_IT(&huart1,&Uart1_Rx_Char,1);
做初始化
主循环中引入Tcp_DataAccept();
重写void Tcp_DataDeal(void){}接受数据 数据存放在Wifi_Command_Buffer
   使用Server_SentTo_Client(*s);向客户端发送数据
*/
#include "main.h"
#include "usart.h"
#include "stdio.h"


extern uint8_t Uart1_Rx_Char;		// 用来接收串口1收到的的数据
extern uint8_t Uart1_Rx_Buffer[100];
extern uint8_t Wifi_Command_Buffer[100];
extern uint8_t Rx_Buffer_Size;
extern uint8_t Rx_Line_Flag;
extern uint8_t Wifi_Get_Command_Flag;


void Server_Init(void);
void Server_SentTo_Client(uint8_t *Str);
uint8_t Strlen(uint8_t *s);
void Strcpy(uint8_t *s1, uint8_t *s2);
uint8_t Strcmp(uint8_t *s1, uint8_t *s2);
void IntToStr(uint32_t num, uint8_t *s);
void Tcp_DataDeal(void);
void Tcp_DataAccept(void);
