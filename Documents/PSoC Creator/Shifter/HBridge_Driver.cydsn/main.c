/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

#define STOP 0x00
#define ALL_ON 0x00
#define FRONT_UP 0x01
#define FRONT_DN 0x02
#define REAR_UP 0x01
#define REAR_DN 0x02

#define FRONT_COMPARE 255;
#define REAR_COMPARE 255;

int main()
{   

    /* Enable the global interrupt */
    CyGlobalIntEnable;
    
	/* Start the components */
    PWM_Start();
    PWM_WriteCompare1(255u);
    PWM_WriteCompare2(255u);
    
    for(;;)
    {
        front_motor_Write(FRONT_UP);
        CyDelay(1500u);
        front_motor_Write(FRONT_DN);
        CyDelay(1500u);
        front_motor_Write(STOP);
        CyDelay(1000u);
      
        
    }
}

/* [] END OF FILE */
