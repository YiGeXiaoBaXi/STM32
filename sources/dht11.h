#ifndef DHT_H
#define DHT_H

#include "stm32f10x.h"
#include "delay.h"

#define IO_DHT11 GPIO_Pin_6 //�����м������������ֲ
#define GPIO_DHT11 GPIOB //�����м������������ֲ
#define DH11_RCC_PORT  RCC_APB2Periph_GPIOB

#define DHT11_DQ_High GPIO_SetBits(GPIO_DHT11,IO_DHT11) 
#define DHT11_DQ_Low  GPIO_ResetBits(GPIO_DHT11,IO_DHT11)

void DHT11_IO_OUT(void);//��ʪ��ģ���������
void DHT11_IO_IN(void); //��ʪ��ģ�����뺯��
void DHT11_Init(void);  //��ʼ��DHT11
u8   DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8   DHT11_Read_Byte(void);             //����һ���ֽ�
u8   DHT11_Read_Bit(void);              //����һ��λ
u8   DHT11_Check(void);                 //����Ƿ����DHT11
void DHT11_Rst(void);                   //��λDHT11  

#endif
