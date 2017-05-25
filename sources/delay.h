#ifndef DELAY_H
#define DELAY_H

#include "stm32f10x.h"

extern void SysTick_Init(void);
extern void Delay_us(__IO u32 nTime);	  //��λ10us

#define Delay_ms(x) Delay_us(1000*x)//��λms

#endif
