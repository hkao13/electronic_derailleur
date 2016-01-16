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

#define SHIFT_IDLE 0x00
#define F_SHIFT_UP 0x01
#define F_SHIFT_DN 0x02
#define R_SHIFT_UP 0x03
#define R_SHIFT_DN 0x04

#define LED_ON 0u
#define LED_OFF 1u

/* UART buffer to store output to console */
char buffer[20] = {0};
/* Variable to hold temporary values */
uint32 regVal = 0x00u;
/* Variable to store the pending shift command */
int shift_command = 0;
/* Initialize the interrupt fuction prototype */
CY_ISR_PROTO(Shifter_ISR); 

int main()
{
    /* Set up interrupt vector address for function */
    gpio_isr_StartEx(Shifter_ISR);
    
    /* Get value of port interrupt configuration register */ 
    regVal = CY_GET_REG32(shifter_switches__INTCFG);
    
    /* Clear the configuration bits for the Pin_Button. 
    Pin_Button_SHIFT is multiplied by 2 as two bits of the interrupt configuration register sets the 
    configuration for one pin */ 
    //regVal &= ~(INTERRUPT_MASK << (shifter_switches_SHIFT * 2)); 
    //CY_SET_REG32(shifter_switches__INTCFG, regVal | (FALLING_EDGE << (shifter_switches_SHIFT * 2)));
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Init the UART module for console debugging */
    UART_Start();  
    UART_UartPutString("PSoC COM ON!\n\r");

    for(;;) 
    {
    } 
}

/* ISR for Shifter commands after gpio_isr is triggered */
CY_ISR(Shifter_ISR)
{
    /* Clear pending interupts from gpio_isr */
    gpio_isr_ClearPending();
    
    /* Check shifter_switches interrupt status register to see which interrupt is
    being triggered. P0.0 for up shift and P0.1 for down shift */
    if(shifter_switches_INTSTAT & (1u << shifter_switches_SHIFT))
    {
        UART_UartPutString("SHIFT UP!\n\r");
        shift_command = F_SHIFT_UP;
    }
    else if (shifter_switches_INTSTAT & (2u << shifter_switches_SHIFT))
    {
        UART_UartPutString("SHIFT DOWN!\n\r");
        shift_command = F_SHIFT_DN;
    }
    else {
        UART_UartPutString("COMMAND UNKNOWN!\n\r");
        shift_command = SHIFT_IDLE;
    }
    /* Clear the interupt caused by shifter_switches */
    shifter_switches_ClearInterrupt();
    
}

/* [] END OF FILE */

