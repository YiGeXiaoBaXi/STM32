#ifndef ADC_H
#define ADC_H

#include "stm32f10x.h"
// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue[3];

void ADC1_Init(void);

#endif
