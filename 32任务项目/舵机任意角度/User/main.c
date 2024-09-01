#include "stm32f10x.h"              
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "Encoder.h"
uint8_t KeyNum;			
float Angle;		

int main(void)
{

	OLED_Init();		
	Servo_Init();		
	Encoder_Init();	

	OLED_ShowString(1, 1, "Angle:");	
	
	while (1)
	{
			Angle+=(float)Encoder_Get(); 			
			if (Angle > 180)			
			{
				Angle = 0;				
			}
			if (Angle < 0)			
			{
				Angle = 180;				
			}
		
		Servo_SetAngle(Angle);			
		OLED_ShowNum(1, 7, Angle, 3);	
}
