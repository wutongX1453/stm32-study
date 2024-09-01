#include "stm32f10x.h"                
#include "PWM.h"                        
#include "Delay.h"
void Servo_Init(void)                 
{
	PWM_Init();
}
 
//1.第1路舵机控制
// 0-500 180-2500  0-180=500-2500 1度等于2000/180
void Servo_SetAngle(float Angle)
{
	PWM_SetCompare(Angle * 2000 / 180 + 500);
 
}
float step=5;
float Now_Angle = 0;
void Servo_P(float Set_Angle)//PID 中的P 通过调整Delay_ms(x)来调速,或者通过调整step步近值来调速
{

	if(Now_Angle >= Set_Angle)
	{
		for(int m = Now_Angle; m >= Set_Angle ; m-=step) 
		{
			Servo_SetAngle(m);
			Delay_ms(50);
		}
	}
	
	if(Now_Angle < Set_Angle)
	{
		for(int n = Now_Angle; n <= Set_Angle ; n+=step) 
		{
			Servo_SetAngle(n);
			Delay_ms(50);
		}
	}
	Now_Angle = Set_Angle;
}

void Servo_PP(float Set_Angle)//PID 中的P 通过调整Delay_ms(x)来调速,或者通过调整step步近值来调速
{   float stepA=1;
	float TOOL;
	TOOL=Now_Angle;
	if(Now_Angle >= Set_Angle)
	{
		for(int m = Now_Angle; m >= Set_Angle ; m-=stepA) 
		{   float ERRO=TOOL-Set_Angle;
	        if(0<=ERRO&&ERRO<30)
	        stepA=1;
	        if(30<=ERRO&&ERRO<100)
	        stepA=5;
	        if(100<=ERRO&&ERRO<180)
	        stepA=20;
			Servo_SetAngle(m);
			Delay_ms(20);
			TOOL-=stepA;
		}
	}
	
	if(Now_Angle < Set_Angle)
	{
		for(int n = Now_Angle; n <= Set_Angle ; n+=stepA) 
		{  float ERRO=Set_Angle-TOOL;
	       if(0<=ERRO&&ERRO<30)
	       stepA=1;
	       if(30<=ERRO&&ERRO<100)
	       stepA=5;
	       if(100<=ERRO&&ERRO<180)
	       stepA=20;
		   Servo_SetAngle(n);
		   Delay_ms(20);
		   TOOL+=stepA;
		}
	}
	Now_Angle = Set_Angle;
}
