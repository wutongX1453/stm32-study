#include "stm32f10x.h"                  // Device header
void PWM_Init(void){
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1 ;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up ;
	TIM_TimeBaseInitStructure.TIM_Period=20000-1;   //ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler=72-1;  //PRC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	TIM_OCInitTypeDef TIM_OCCInitStructure;
	TIM_OCStructInit(&TIM_OCCInitStructure);
	TIM_OCCInitStructure.TIM_OCMode= TIM_OCMode_PWM1 ;
	TIM_OCCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High ;
	TIM_OCCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCCInitStructure.TIM_Pulse=0;         //CCR
    TIM_OC2Init(TIM2,&TIM_OCCInitStructure);
	
	TIM_Cmd(TIM2,ENABLE);
	





}


void 	PWM_SetCompare2(uint16_t Compare)
{
   TIM_SetCompare2(TIM2,Compare);

}