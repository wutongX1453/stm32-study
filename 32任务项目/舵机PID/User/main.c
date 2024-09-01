#include "stm32f10x.h"                  
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
uint16_t num = 0;
int i ;
int  main(void)
{
	OLED_Init();                
	OLED_ShowChar(1,1,'B');     
	Servo_Init();               
 
	while(1)
	{   Servo_PP(0);
		Delay_ms(10);
		Servo_PP(180);
		Delay_ms(10);
		
	}
 
}