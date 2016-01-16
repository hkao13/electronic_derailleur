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
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#define INTERRUPT_MASK 0x03
#define RISING_EDGE 0x01
#define FALLING_EDGE 0x02

#define LED_ON 0u
#define LED_OFF 1u

/* UART buffer to store output to console */
char buffer[20] = {0};

/* LED state variable */
uint8 ledstate = 0u;

/* Initialize the interrupt fuction prototype */
CY_ISR_PROTO(Switch_Debounce_ISR); 


int main()
{
    uint32 regVal = 0x00u;
      
    
    /* Set up interrupt vector address for function */
    gpio_isr_StartEx(Switch_Debounce_ISR);
    
    /* Get value of port interrupt configuration register */ 
    regVal = CY_GET_REG32(shifter_switches__INTCFG);
    
    /* Clear the configuration bits for the Pin_Button. 
    Pin_Button_SHIFT is multiplied by 2 as two bits of the interrupt configuration register sets the 
    configuration for one pin */ 
    //regVal &= ~(INTERRUPT_MASK << (shifter_switches_SHIFT * 2));
    
    //CY_SET_REG32(shifter_switches__INTCFG, regVal | (FALLING_EDGE << (shifter_switches_SHIFT * 2)));
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();  
    UART_UartPutString("PSoC COM ON!\n\r");

    for(;;) 
    {
        Pin_LED_Write(LED_OFF);
        //sprintf(buffer, "%lu\n\r", CY_SYS_PINS_READ_PIN(shifter_switches__PS, shifter_switches_1_SHIFT));
        //UART_UartPutString(buffer);
    } 
}

CY_ISR(Switch_Debounce_ISR)
{
    gpio_isr_ClearPending();
    
    //shifter_switches_ClearInterrupt();
    
    /* Turn On the LED */
    //Pin_LED_Write(LED_ON);

    /* Cause nested software interrupt after 1000 ms */
    //CyDelay(1000u);
    //CyIntSetPending(NESTED_ISR);

    /* Turn Off the LED */
    //Pin_LED_Write(LED_OFF);
    
    if(shifter_switches_INTSTAT & (1u << shifter_switches_SHIFT))
    {
        UART_UartPutString("SHIFT UP!\n\r");
    }
    shifter_switches_ClearInterrupt();
    
}

/* [] END OF FILE */

