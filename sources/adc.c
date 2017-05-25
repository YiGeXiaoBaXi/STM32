#include "adc.h"
#ifdef ADC_H

#define ADC1_DR_Address    ((u32)0x40012400+0x4c)

__IO uint16_t ADC_ConvertedValue[3];


// /*
//  * ��������ADC1_GPIO_Config
//  * ����  ��ʹ��ADC1��DMA1��ʱ�ӣ���ʼ��PC.01
//  * ����  : ��
//  * ���  ����
//  * ����  ���ڲ�����
//  */
// static void ADC1_GPIO_Config(void)
// {
// 	GPIO_InitTypeDef GPIO_InitStructure;
	
// 	/* Enable DMA clock */
// 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
// 	/* Enable ADC1 and GPIOC clock */
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
	
// 	/* Configure PC.01  as analog input */
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
// 	GPIO_Init(GPIOC, &GPIO_InitStructure);				// PC1,����ʱ������������
// }


// /* ��������ADC1_Mode_Config
//  * ����  ������ADC1�Ĺ���ģʽΪMDAģʽ
//  * ����  : ��
//  * ���  ����
//  * ����  ���ڲ�����
//  */
// static void ADC1_Mode_Config(void)
// {
// 	DMA_InitTypeDef DMA_InitStructure;
// 	ADC_InitTypeDef ADC_InitStructure;
	
// 	/* DMA channel1 configuration */
// 	DMA_DeInit(DMA1_Channel1);
// 	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;	 //ADC��ַ
// 	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;//�ڴ��ַ
// 	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
// 	DMA_InitStructure.DMA_BufferSize = 1;
// 	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ�̶�
// 	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;  //�ڴ��ַ�̶�
// 	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//����
// 	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
// 	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		//ѭ������
// 	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
// 	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
// 	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
// 	/* Enable DMA channel1 */
// 	DMA_Cmd(DMA1_Channel1, ENABLE);
	
// 	/* ADC1 configuration */
	
// 	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//����ADCģʽ
// 	ADC_InitStructure.ADC_ScanConvMode = DISABLE ; 	 //��ֹɨ��ģʽ��ɨ��ģʽ���ڶ�ͨ���ɼ�
// 	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//��������ת��ģʽ������ͣ�ؽ���ADCת��
// 	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//��ʹ���ⲿ����ת��
// 	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 	//�ɼ������Ҷ���
// 	ADC_InitStructure.ADC_NbrOfChannel = 1;	 	//Ҫת����ͨ����Ŀ1
// 	ADC_Init(ADC1, &ADC_InitStructure);
	
// 	/*����ADCʱ�ӣ�ΪPCLK2��8��Ƶ����9Hz*/
// 	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
// 	/*����ADC1��ͨ��11Ϊ55.	5���������ڣ�����Ϊ1 */ 
// 	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_55Cycles5);
	
// 	/* Enable ADC1 DMA */
// 	ADC_DMACmd(ADC1, ENABLE);
	
// 	/* Enable ADC1 */
// 	ADC_Cmd(ADC1, ENABLE);
	
// 	/*��λУ׼�Ĵ��� */   
// 	ADC_ResetCalibration(ADC1);
// 	/*�ȴ�У׼�Ĵ�����λ��� */
// 	while(ADC_GetResetCalibrationStatus(ADC1));
	
// 	/* ADCУ׼ */
// 	ADC_StartCalibration(ADC1);
// 	/* �ȴ�У׼���*/
// 	while(ADC_GetCalibrationStatus(ADC1));
	
// 	/* ����û�в����ⲿ����������ʹ���������ADCת�� */ 
// 	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
// }

/*
 * ��������ADC1_GPIO_Config
 * ����  ��ʹ��ADC1��DMA1��ʱ�ӣ���ʼ��PC.01
 * ����  : ��
 * ���  ����
 * ����  ���ڲ�����
 */
static void ADC1_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable DMA clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	/* Enable ADC1 and GPIOC clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
	
	/* Configure PC.01  as analog input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;				 //��ʼ������1,2,3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);				// PC1,����ʱ������������
}


/* ��������ADC1_Mode_Config
 * ����  ������ADC1�Ĺ���ģʽΪMDAģʽ
 * ����  : ��
 * ���  ����
 * ����  ���ڲ�����
 */
static void ADC1_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	/* DMA channel1 configuration */
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;	 //ADC��ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC_ConvertedValue;//�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 3;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ�̶�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�̶�
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//����
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		//ѭ������
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	/* Enable DMA channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	/* ADC1 configuration */
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//����ADCģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 	 //��ֹɨ��ģʽ��ɨ��ģʽ���ڶ�ͨ���ɼ�
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//��������ת��ģʽ������ͣ�ؽ���ADCת��
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//��ʹ���ⲿ����ת��
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 	//�ɼ������Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 3;	 	//Ҫת����ͨ����Ŀ1
	ADC_Init(ADC1, &ADC_InitStructure);
	
	/*����ADCʱ�ӣ�ΪPCLK2��8��Ƶ����9Hz*/ //6  12MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	/*����ADC1��ͨ��11Ϊ55.	5���������ڣ�����Ϊ1 */ 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_28Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 2, ADC_SampleTime_28Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 3, ADC_SampleTime_28Cycles5);

	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);
	
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	
	/*��λУ׼�Ĵ��� */   
	ADC_ResetCalibration(ADC1);
	/*�ȴ�У׼�Ĵ�����λ��� */
	while(ADC_GetResetCalibrationStatus(ADC1));
	
	/* ADCУ׼ */
	ADC_StartCalibration(ADC1);
	/* �ȴ�У׼���*/
	while(ADC_GetCalibrationStatus(ADC1));
	
	/* ����û�в����ⲿ����������ʹ���������ADCת�� */ 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

// void ADC1S_Init(void)//ת������ (1/72000000)*6*(12.5+28.5)=3.41us     3.41*5=17.5us
// {
// 	ADC_InitTypeDef ADC_InitStructure;					//ADC��ʼ���ṹ��
// 	DMA_InitTypeDef DMA_InitStructure;					//DMA��ʼ���ṹ��
// 	GPIO_InitTypeDef  GPIO_InitStructure;				//GPIO��ʼ���ṹ��
// 	RCC_ADCCLKConfig(RCC_PCLK2_Div6);					//PLL��ʱ�ӣ���Ϊ72MHz��6��Ƶ����ΪADCʱ�ӣ�12MHz�����Ϊ14MHz��
// 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);   //ʹ��DMA1ʱ��
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 	| RCC_APB2Periph_AFIO, ENABLE);						//ʹ��ADC1ʱ�ӣ������Ÿ���ʱ��
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��

// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;				 //��ʼ������1,2,3
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		 //ģ������
// 	GPIO_Init(GPIOC, &GPIO_InitStructure);				 //��ʼ��GPIOA	

// 	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	 //ADC�����ڶ���ģʽ
// 	ADC_InitStructure.ADC_ScanConvMode = ENABLE;		 //����ɨ��ģʽ
// 	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	 //����ת��
// 	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�ⲿ����ת�����عر�
// 	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//���ݶ��뷽ʽ���Ҷ���
// 	ADC_InitStructure.ADC_NbrOfChannel = 5;				 //����5��ת��ͨ��
// 	ADC_Init(ADC1, &ADC_InitStructure);					 //��ʼ��ADC1	
// 	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_28Cycles5);//����ADC1ͨ��0��ת��˳��Ϊ��1˳λ������ʱ��28.5������    
// 	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_28Cycles5);
// 	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_28Cycles5);
// 	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_28Cycles5);
// 	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_28Cycles5);	
// 	ADC_DMACmd(ADC1, ENABLE); 							//����ADC1��DMAͨ��
// 	ADC_Cmd(ADC1, ENABLE);								//����ADC1
// 	ADC_ResetCalibration(ADC1);							//��λADC1��У׼�Ĵ���
// 	while(ADC_GetResetCalibrationStatus(ADC1));			//�ȴ���λ���
// 	ADC_StartCalibration(ADC1);							//��ʼָ��ADC1��У׼״̬
// 	while(ADC_GetCalibrationStatus(ADC1));				//��ȡ״̬����Ϊ����״̬��ȴ�
// 	ADC_SoftwareStartConvCmd(ADC1, ENABLE);				//����ADC1���������������ʼת����	
// 	DMA_DeInit(DMA1_Channel1);							//��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
// 	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;//DMA����ADC����ַ
// 	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC1_ConvertedValues;	//DMA�ڴ����ַ
// 	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	 //�ڴ���Ϊ���ݴ����Ŀ�ĵ�
// 	DMA_InitStructure.DMA_BufferSize = 5;				 //DMAͨ����DMA����Ĵ�С
// 	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ�Ĵ�������
// 	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//�ڴ��ַ�Ĵ�������
// 	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//���ݿ��Ϊ16λ
// 	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//���ݿ��Ϊ16λ
// 	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		    //������ѭ������ģʽ
// 	DMA_InitStructure.DMA_Priority = DMA_Priority_High;		//DMAͨ��1ӵ�и����ȼ�
// 	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;			//DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
// 	DMA_Init(DMA1_Channel1, &DMA_InitStructure);  			//��ʼ��DMA��ͨ��	
// 	DMA_Cmd(DMA1_Channel1, ENABLE);							 //����DMAͨ��
// }

/*
 * ��������ADC1_Init
 * ����  ����
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void ADC1_Init(void)
{
	ADC1_GPIO_Config();
	ADC1_Mode_Config();
}


#endif
