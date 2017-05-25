#ifndef DS18B20_H
#define DS18B20_H

#include "stm32f10x.h"
#include "delay.h"

#define  SkipROM    0xCC  //����ROM
#define  SearchROM  0xF0  //����ROM
#define  ReadROM    0x33  //��ROM
#define  MatchROM   0x55  //ƥ��ROM
#define  AlarmROM   0xEC  //�澯ROM

#define  StartConvert    0x44  //��ʼ�¶�ת�������¶�ת���ڼ����������0��ת�����������1
#define  ReadScratchpad  0xBE  //���ݴ�����9���ֽ�
#define  WriteScratchpad 0x4E  //д�ݴ������¶ȸ澯TH��TL
#define  CopyScratchpad  0x48  //���ݴ������¶ȸ澯���Ƶ�EEPROM���ڸ����ڼ����������0������������1
#define  RecallEEPROM    0xB8    //��EEPROM���¶ȸ澯���Ƶ��ݴ����У������ڼ����0��������ɺ����1
#define  ReadPower       0xB4    //����Դ�Ĺ��緽ʽ��0Ϊ������Դ���磻1Ϊ�ⲿ��Դ����


#define EnableINT()  
#define DisableINT()

#define DS_PORT   GPIOB           //DS18B20���ӿ�
#define DS_DQIO   GPIO_Pin_7      //GPIOA1
#define DS_RCC_PORT  RCC_APB2Periph_GPIOB

#define DS_PRECISION 0x7f   //�������üĴ��� 1f=9λ; 3f=10λ; 5f=11λ; 7f=12λ;
#define DS_AlarmTH  0x64
#define DS_AlarmTL  0x8a
#define DS_CONVERT_TICK 1000

#define ResetDQ() GPIO_ResetBits(DS_PORT,DS_DQIO)
#define SetDQ()  GPIO_SetBits(DS_PORT,DS_DQIO)
#define GetDQ()  GPIO_ReadInputDataBit(DS_PORT,DS_DQIO)


void DS18B20_Init(void);
float DS18B20_Read(void);

#endif
