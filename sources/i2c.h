#ifndef I2C_H
#define I2C_H

#include "stm32f10x.h"
#include "delay.h"

// //IO��������
// #define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=4<<12;} //��������
// #define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=7<<12;} //��©���50Mhz

// //IO��������	 
// #define IIC_SCL_SET GPIO_SetBits(GPIOB,GPIO_Pin_10)
// #define IIC_SCL_CLR GPIO_ResetBits(GPIOB,GPIO_Pin_10)
// #define IIC_SDA_SET GPIO_SetBits(GPIOB,GPIO_Pin_11)
// #define IIC_SDA_CLR GPIO_ResetBits(GPIOB,GPIO_Pin_11) 
// #define READ_SDA    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) //����SDA 

//IO��������
#define SDA_IN()  {GPIOG->CRH &= 0XF0FFFFFF; GPIOG->CRH |= 4 << 24;} //��������
#define SDA_OUT() {GPIOG->CRH &= 0XF0FFFFFF; GPIOG->CRH |= 7 << 24;} //��©���50Mhz

//IO��������	 
#define IIC_SCL_SET GPIO_SetBits(GPIOG,GPIO_Pin_13)
#define IIC_SCL_CLR GPIO_ResetBits(GPIOG,GPIO_Pin_13)
#define IIC_SDA_SET GPIO_SetBits(GPIOG,GPIO_Pin_14)
#define IIC_SDA_CLR GPIO_ResetBits(GPIOG,GPIO_Pin_14) 
#define READ_SDA    GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_14) //����SDA 

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

//void SDA_IN(void);
//void SDA_OUT(void);

#endif

