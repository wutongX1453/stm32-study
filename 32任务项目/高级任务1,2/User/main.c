#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "sys.h"
#include "Servo.h"
float pitch,roll,yaw;

int main(void)
{   Servo_Init();
	OLED_Init();
	uart1_init(9600);	
	mpu_dmp_init();
	while (1)
	{
		mpu_dmp_get_data(&pitch,&roll,&yaw);		
		printf("%.2f %.2f %.2f\r\n",pitch,roll,yaw);
		delay_ms(50);
		OLED_ShowSignedNum(1, 1,pitch, 2);
		OLED_ShowSignedNum(2, 1,roll, 2);
		OLED_ShowSignedNum(3, 1,yaw, 2);
		Servo_SetAngle(yaw);//保持方向不变Servo_SetAngle(-yaw);
		OLED_ShowSignedNum(4, 1,-yaw, 2);
	}
}
