#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "Encoder.h"
#include "HC-08.h"
#include "HC05.h"

uint8_t RxSTA = 1;
char RxData[100] = "0000";

int main(void)
{
	OLED_Init();
	HC05_Init();
	OLED_ShowString(1, 1, "RxData:");
	OLED_ShowString(2, 1, RxData);
	Encoder_Init();
	Servo_Init();
	while (1)
	{
		HC05_GetData(RxData);
		//if(RxData[0]=='a'){
		//Servo_SetAngle(60);	
		//}
		if(RxData[0]=='1'){
		Servo_SetAngle(30);	
		RxData[0]='0';
		}
		if(RxData[1]=='1'){
		Servo_SetAngle(60);	
		RxData[1]='0';
		}
		if(RxData[2]=='1'){
		Servo_SetAngle(90);	
		RxData[2]='0';
		}
		if(RxData[3]=='1'){
		Servo_SetAngle(120);	
		RxData[3]='0';
		}
			if(RxData[3]=='c'){
		Servo_SetAngle(120);	
		}
		if (RxSTA == 0)
		{
			OLED_Clear();
			OLED_ShowString(1, 1, "RxData:");
			OLED_ShowString(2, 1, RxData);
			RxSTA = 1;
		}
	
	}
}

//int16_t Num;
//float angle;
//int main(){
//	OLED_Init();
//	Encoder_Init();
//	OLED_ShowString(1, 1, "Num:");
//	Servo_Init();
//	while(1){
	

	//if(angle>180){
	//angle=0;}
	//Servo_SetAngle(angle);
//	Num += Encoder_Get();				//获取自上此调用此函数后，旋转编码器的增量值，并将增量值加到Num上
//	OLED_ShowSignedNum(1, 5, Num, 5);	//显示Num
//	angle+=(float)Encoder_Get();
//	OLED_ShowSignedNum(2,5,angle,5);
	
//	}

// }
