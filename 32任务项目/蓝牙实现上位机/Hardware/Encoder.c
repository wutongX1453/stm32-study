#include "stm32f10x.h" 

uint16_t Encoder_Count;

void  Encoder_Init(void)
{

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line=EXTI_Line0|EXTI_Line1;
	EXTI_InitStructure.EXTI_LineCmd= ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2);
	NVIC_InitTypeDef  NVIC_InitSructure;
	NVIC_InitSructure.NVIC_IRQChannel=EXTI0_IRQn  ;
	NVIC_InitSructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitSructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitSructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitSructure);
	NVIC_InitSructure.NVIC_IRQChannel=EXTI1_IRQn  ;
	NVIC_InitSructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitSructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitSructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitSructure);	

}

int16_t Encoder_Get(void)
{   int16_t temp;
	temp=Encoder_Count;
	Encoder_Count=0;
	return temp;
}

void  EXTI0_IRQHandler(void){

if(EXTI_GetITStatus(EXTI_Line0)==SET)
{
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
	{
		Encoder_Count--;
	}
	
	EXTI_ClearITPendingBit(EXTI_Line0);
}

}

void  EXTI1_IRQHandler(void){

if(EXTI_GetITStatus(EXTI_Line1)==SET)
{
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
	{
		Encoder_Count++;
	}
	
	EXTI_ClearITPendingBit(EXTI_Line1);
}

}