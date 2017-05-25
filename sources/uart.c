#include "uart.h"
#ifdef UART_H

__IO uint8_t Uart1Front;
__IO uint8_t Uart1Rear;
__IO uint8_t Uart1Cnt;
__IO uint8_t Uart1Sta;
__IO char Uart1Buffer[256];
char Uart1Buff[64];

__IO uint8_t Uart2Front;
__IO uint8_t Uart2Rear;
__IO uint8_t Uart2Cnt;
__IO uint8_t Uart2Sta;
__IO char Uart2Buffer[256];
char Uart2Buff[64];

__IO uint8_t Uart3Front;
__IO uint8_t Uart3Rear;
__IO uint8_t Uart3Cnt;
__IO uint8_t Uart3Sta;
__IO char Uart3Buffer[256];
char Uart3Buff[64];

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


void Uart1_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1,GPIOAʱ��
	USART_DeInit(USART1);//��λ����1
	//USART1_TX PA9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PA.10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//Usart1 NVIC ����

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�5
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//��ʼ��VIC�Ĵ���
	  
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;//��У��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//ʹ�ܽ��շ���
	
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
	USART_Cmd(USART1, ENABLE);	

}

void Uart2_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��PORTAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //ʹ��USART2
	USART_DeInit(USART2);  //��λ����2
	//USART2_TX   PA.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA2

	//USART2_RX	  PA.3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA3     

	//Usart1 NVIC ����

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	/* USARTx configured as follow:
	- BaudRate = 9600 baud  ������
	- Word Length = 8 Bits  ���ݳ���
	- One Stop Bit          ֹͣλ
	- No parity             У�鷽ʽ
	- Hardware flow control disabled (RTS and CTS signals) Ӳ��������
	- Receive and transmit enabled                         ʹ�ܷ��ͺͽ���
	*/
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 

}

void Uart3_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��PORTAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //ʹ��USART2
	USART_DeInit(USART3);  //��λ����2
	//USART2_TX   PA.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PA.2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��PA2

	//USART2_RX	  PA.3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PA3     

	//Usart1 NVIC ����

	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	/* USARTx configured as follow:
	- BaudRate = 9600 baud  ������
	- Word Length = 8 Bits  ���ݳ���
	- One Stop Bit          ֹͣλ
	- No parity             У�鷽ʽ
	- Hardware flow control disabled (RTS and CTS signals) Ӳ��������
	- Receive and transmit enabled                         ʹ�ܷ��ͺͽ���
	*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 

}

PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	//USART_ClearFlag(USART1, USART_FLAG_TC);//���������ɱ�־λ,������ܻᶪʧ��1���ֽڵ�����.
	USART_SendData(USART1, (uint8_t) ch);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}

	return ch;
}

void USART1_Putchar(char ch)
{
	USART_SendData(USART1, (uint8_t) ch);
 	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}
}

void USART2_Putchar(char ch)
{
	USART_SendData(USART2, (uint8_t) ch);
 	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET) {}
}

void USART3_Putchar(char ch)
{
	USART_SendData(USART3, (uint8_t) ch);
 	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {}
}

void USART1_Puts(char *string)
{
	//USART_ClearFlag(USART1, USART_FLAG_TC);//���������ɱ�־λ,������ܻᶪʧ��1���ֽڵ�����.
	while(*string)
	{
		USART_SendData(USART1, (uint8_t) *string++);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}
	}
}

void USART2_Puts(char *string)
{
	while(*string)
	{
		USART_SendData(USART2, (uint8_t) *string++);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET) {}
	}
}

void USART3_Puts(char *string)
{
	//USART_ClearFlag(USART3, USART_FLAG_TC);//���������ɱ�־λ,������ܻᶪʧ��1���ֽڵ�����.
	while(*string)
	{
		USART_SendData(USART3, (uint8_t) *string++);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {}
	}
}
void USART3_PutData(char *string, uint8_t num)
{
	//USART_ClearFlag(USART3, USART_FLAG_TC);//���������ɱ�־λ,������ܻᶪʧ��1���ֽڵ�����.
	while(num-- > 0)
	{
		USART_SendData(USART3, (uint8_t) *string++);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {}
	}
}

//����1�ж� 
void USART1_IRQHandler(void)  
{
	// if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET) //�жϲ��� 
	// { 
	// 	USART_ClearITPendingBit(USART1,USART_IT_RXNE); //����жϱ�־
	// 	Uart1Buffer[Uart1Rear] = USART_ReceiveData(USART1); 
	// 	Uart1Rear++; 
	// 	Uart1Rear &= 0x3F; 
	// } 
	// if(Uart1Buffer[Uart1Rear-1] == 0x5A) //ͷ 
	// 	Uart1Front = Uart1Rear-1; 
	// if((Uart1Buffer[Uart1Front] == 0x5A)&&(Uart1Buffer[Uart1Rear-1] == 0xA5)) //��⵽ͷ������¼�⵽β 
	// { 
	//     Uart1Cnt = Uart1Rear-1- Uart1Front - 1; //���� 
	//     Uart1Sta = 1; //��־λ 
	// } 
	// if(USART_GetFlagStatus(USART1,USART_FLAG_ORE) == SET) //��� 
	// { 
	//     USART_ClearFlag(USART1,USART_FLAG_ORE); //��SR 
	//     USART_ReceiveData(USART1); //��DR 
	// } 

	uint8_t ch;
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)  
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		ch = USART_ReceiveData(USART1);
		printf("%c", ch);
		USART_SendData(USART1, USART_ReceiveData(USART1));   
		//USART1_Putchar('a');
		USART1_Puts("Usart1 interrupt\r\n");
	}   
}


//����2�ж� 
void USART2_IRQHandler(void)  
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET) //�жϲ��� 
	{ 
		USART_ClearITPendingBit(USART2,USART_IT_RXNE); //����жϱ�־
		Uart2Buffer[Uart2Rear] = USART_ReceiveData(USART2); 
		Uart2Rear++; 
		Uart2Rear &= 0x3F; 
	} 
	if(Uart2Buffer[Uart2Rear-1] == 0x5A) //ͷ 
		Uart2Front = Uart2Rear-1; 
	if((Uart2Buffer[Uart2Front] == 0x5A)&&(Uart2Buffer[Uart2Rear-1] == 0x0D)) //��⵽ͷ������¼�⵽β 
	{ 
	    Uart2Cnt = Uart2Rear-1- Uart2Front - 1; //���� 
	    Uart2Sta = 1; //��־λ 
	} 
	if(USART_GetFlagStatus(USART2,USART_FLAG_ORE) == SET) //��� 
	{ 
	    USART_ClearFlag(USART2,USART_FLAG_ORE); //��SR 
	    USART_ReceiveData(USART2); //��DR 
	}
}
	// //uint8_t ch;
 //    if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET)  
 //    {
 //    	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	// 	//ch = USART_ReceiveData(USART2);
	// 	//printf("%c", ch);
	// 	USART_SendData(USART2, USART_ReceiveData(USART2));
	// 	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET) {};

	// 	//USART2_Puts("usart2 interrupt\r\n");             
 //    }
//}
		// if(Uart1Sta){
		// 	memset(Uart1Buff, 0, 64);
		// 	memcpy(Uart1Buff, &Uart1Buffer[Uart1Front + 1], Uart1Cnt);
		// 	USART1_Puts(Uart1Buff);
		// // for(i = 0; i <= Uart1Cnt; i++)
		// // {
		// // 	USART1_Putchar(Uart1Buffer[Uart1Front + i]);
		// // }
		// Uart1Front = 0;
		// Uart1Rear = 0;
		// Uart1Sta = 0;
		// }
void USART3_IRQHandler(void)  
{
	// uint8_t ch;
	// if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)  
	// {
	// 	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
	// 	ch = USART_ReceiveData(USART3);
	// 	printf("%c", ch);
	// 	USART_SendData(USART3, USART_ReceiveData(USART3));   
	// 	//USART1_Putchar('a');
	// 	//USART1_Puts("Usart1 interrupt\r\n");
	// }   
	if(USART_GetITStatus(USART3,USART_IT_RXNE) != RESET) //�жϲ��� 
	{ 
		USART_ClearITPendingBit(USART3,USART_IT_RXNE); //����жϱ�־
		Uart3Buffer[Uart3Rear] = USART_ReceiveData(USART3); 
		Uart3Rear++; 
		Uart3Rear &= 0x3F; 
	} 
	if(Uart3Buffer[Uart3Rear-1] == 0x5A) //ͷ 
		Uart3Front = Uart3Rear-1; 
	if((Uart3Buffer[Uart3Front] == 0x5A)&&(Uart3Buffer[Uart3Rear-1] == 0xA5)) //��⵽ͷ������¼�⵽β 
	{ 
	    Uart3Cnt = Uart3Rear-1- Uart3Front - 1; //���� 
	    Uart3Sta = 1; //��־λ 
	} 
	if(USART_GetFlagStatus(USART3,USART_FLAG_ORE) == SET) //��� 
	{ 
	    USART_ClearFlag(USART3,USART_FLAG_ORE); //��SR 
	    USART_ReceiveData(USART3); //��DR 
	}
}

#endif
