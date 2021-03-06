#include "main.h"

// Improvements direction: Acceleration filter, increasing the proportion of the acceleration correction in quaternion
// Remote control command smoothing

char id[3];
unsigned char USART_BUF[24] = {0};

int main(void)
{
    int i = 0;
    BSP_Init();    
    //delay 500ms, wait MPU6050 for stable signal  
    delay_ms(500);    
    while(MPU6050_Initialization() == 0xff) 
    {
        i++;     // try again if initialization failed          
        if(i>10) // buzzer starts if initialization fail for more than 10 times and give up
        {
            while(1) 
            {
                LED1_TOGGLE();
                delay_ms(50);
                
            }
        }  
    }    
    MPU6050_Gyro_calibration();
    
    MPU6050_Interrupt_Configuration(); 
        
    PWM_Configuration();        
    // Set the duty cycle to 1000 to initialize the motor controller for friction wheels
    PWM1 = 1000;
    PWM2 = 1000;    
    delay_ms(1000);
    
    // initialize the motor controller for bullets sending motor
    Motor_Reset(MOTOR_NUM1);    
    delay_ms(30);       
    Motor_Init(MOTOR_NUM1,PWM_MODE);
    delay_ms(30);	
    
    while(1)
    {
        CurrentProtect(); // Overcurrent protection for motor controller
    }
}


