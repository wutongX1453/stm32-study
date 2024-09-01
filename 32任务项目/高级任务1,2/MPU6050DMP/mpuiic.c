#include "mpuiic.h"
#include "delay.h"


void MPU_IIC_Delay(void)
{
	delay_us(2);
}


void MPU_IIC_Init(void)
{			
	//GPIO_InitTypeDef GPIO_InitStructure;
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	 *(unsigned int*)0x40021018 |= (1<<3);
	//GPIO_InitStructure.GPIO_Pin = MPU6050_IIC_SCL_Pin/*|MPU6050_IIC_SDA_Pin;*/	;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     
	//GPIO_Init(GPIOB, &GPIO_InitStructure);	
	GPIOB->CRH&=~( 0xFF<<12); 
	GPIOB->CRH|=(3<<12)|(3<<8);
    //GPIOB->CRH&=~( 0x0F<<8); 
	//GPIOB->CRH|=(3<<8);		
}

void MPU6050_IIC_SDA_IO_OUT(void)
{

	//GPIO_InitTypeDef GPIO_InitStructure;
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    *(unsigned int*)0x40021018 |= (1<<3);	
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
   // *(unsigned int*)(0x40010C00+0x04) |= (0011000000000000);	//GPIOB_CRH(0011)?
	//*(unsigned int*)(0x40010C00+0x04) &= ~(1100111111111111);
	GPIOB->CRH&=~( 0x0F<<12); 
	 GPIOB->CRH|=(3<<12);	
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    	
	//GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void MPU6050_IIC_SDA_IO_IN(void)
{

	//GPIO_InitTypeDef GPIO_InitStructure;
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    *(unsigned int*)0x40021018 |= (1<<3);	
	//GPIO_InitStructure.GPIO_Pin =MPU6050_IIC_SDA_Pin;	
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;     
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     
	//GPIO_Init(GPIOB, &GPIO_InitStructure);
	 GPIOB->CRH&=~( 0x0F<<12); 
	 GPIOB->CRH|=( 0x04<<12); 
}

void MPU_IIC_Start(void)
{
	MPU6050_IIC_SDA_IO_OUT(); 
	MPU_IIC_SDA=1;	  	  
	MPU_IIC_SCL=1;
	MPU_IIC_Delay();
 	MPU_IIC_SDA=0;
	MPU_IIC_Delay();
	MPU_IIC_SCL=0;
}	  

void MPU_IIC_Stop(void)
{
	MPU6050_IIC_SDA_IO_OUT();
	MPU_IIC_SCL=0;
	MPU_IIC_SDA=0;
 	MPU_IIC_Delay();
	MPU_IIC_SCL=1;  
	MPU_IIC_SDA=1;
	MPU_IIC_Delay();							   	
}

u8 MPU_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	MPU6050_IIC_SDA_IO_IN();      
	MPU_IIC_SDA=1;MPU_IIC_Delay();	   
	MPU_IIC_SCL=1;MPU_IIC_Delay();	 
	while(MPU_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			MPU_IIC_Stop();
			return 1;
		}
	}
	MPU_IIC_SCL=0;   
	return 0;  
} 

void MPU_IIC_Ack(void)
{
	MPU_IIC_SCL=0;
	MPU6050_IIC_SDA_IO_OUT();
	MPU_IIC_SDA=0;
	MPU_IIC_Delay();
	MPU_IIC_SCL=1;
	MPU_IIC_Delay();
	MPU_IIC_SCL=0;
}	    
void MPU_IIC_NAck(void)
{
	MPU_IIC_SCL=0;
	MPU6050_IIC_SDA_IO_OUT();
	MPU_IIC_SDA=1;
	MPU_IIC_Delay();
	MPU_IIC_SCL=1;
	MPU_IIC_Delay();
	MPU_IIC_SCL=0;
}					 				     			  
void MPU_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	MPU6050_IIC_SDA_IO_OUT(); 	    
    MPU_IIC_SCL=0;
    for(t=0;t<8;t++)
    {              
        MPU_IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		MPU_IIC_SCL=1;
		MPU_IIC_Delay(); 
		MPU_IIC_SCL=0;	
		MPU_IIC_Delay();
    }	 
} 	     
u8 MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	MPU6050_IIC_SDA_IO_IN();
    for(i=0;i<8;i++ )
	{
        MPU_IIC_SCL=0; 
        MPU_IIC_Delay();
		MPU_IIC_SCL=1;
        receive<<=1;
        if(MPU_READ_SDA)receive++;   
		MPU_IIC_Delay(); 
    }					 
    if (!ack)
        MPU_IIC_NAck();
    else
        MPU_IIC_Ack();
    return receive;
}


















