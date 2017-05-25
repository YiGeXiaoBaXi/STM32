#include "key.h"
#ifdef KEY_H

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//��PA PE��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //��������ģʽ
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //��������ģʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t KEY_Scan(uint8_t mode)
{	 
	static uint8_t key_up = 1;//�����ɿ���־
	if(mode)
		key_up = 1;  //֧������		  
	if(key_up && (S1==0 || S2==0 || S3==0 || S4==1))
	{
		Delay_ms(10);//ȥ����
		key_up = 0;
		if(S1 == 0) return 1;
		else if(S2==0) return 2;
		else if(S3==0) return 3;
		else if(S4==1) return 4;
	}else if(S1 == 1 && S2 == 1 && S3 == 1 && S4 == 0)
		key_up = 1; 	    
 	return 0;//�ް�������
}

#endif
