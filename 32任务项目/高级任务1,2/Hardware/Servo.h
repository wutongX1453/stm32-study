#ifndef __SERVO_H
#define __SERVO_H

void Servo_Init(void);
void Servo_SetAngle(float Angle);
void Servo_P(float Set_Angle);
void Servo_PP(float Set_Angle);

#endif
