#include "main.h"
#include "math.h"

#define Sample_Num 233 //每一个通道的采样数
#define Channel_Num  2//通道数量， 一个为电压量，一个为电流量。

extern uint32_t ADC_Value[Sample_Num][Channel_Num];
extern uint8_t Dma_DataDeal_Flag;
extern float ADC_Value_Buffer[Sample_Num][Channel_Num];
extern float ADC_ValueAverage[Channel_Num];

void Update_Data(void);
void Data_Fliter(void);
