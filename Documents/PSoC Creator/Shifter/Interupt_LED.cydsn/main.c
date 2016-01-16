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

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    char buffer[20] = {0};
    
    /*Variable to save temporary data*/
    uint32 regVal = 0x00u;
    
    /*Flag to switch interrupt type*/
    uint8 edgeFlag = 0x00u;
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    
    UART_UartPutString("PSoC COM ON!\n\r");

    for(;;) 
    { 
        /* Get value of port interrupt configuration register */ 
        regVal = CY_GET_REG32(Pin_Button__INTCFG);
        //sprintf(buffer, "regVal: %lu \n\r", regVal);
        //UART_UartPutString(buffer);
        /* Clear the configuration bits for the Pin_Button. 
        Pin_Button_SHIFT is multiplied by 2 as two bits of the interrupt configuration register sets the 
        configuration for one pin */ 
        regVal &= ~(INTERRUPT_MASK << (Pin_Button_SHIFT * 2));
        //sprintf(buffer, "regVal: %lu \n\r", regVal);
        //UART_UartPutString(buffer);
        //sprintf(buffer, "interrupt mask: %d \n\r", INTERRUPT_MASK);
        //UART_UartPutString(buffer);
        //sprintf(buffer, "pin button shift: %d \n\r", Pin_Button_SHIFT);
        //UART_UartPutString(buffer);
        
        if(edgeFlag) 
        { 
            /* Set P0[7] to GPIO interrupt rising-edge trigger. 
            Pin_Button_SHIFT is multiplied by 2 as two bits of the interrupt configuration register sets the configuration for one pin */ 
            CY_SET_REG32(Pin_Button__INTCFG, regVal | (RISING_EDGE << (Pin_Button_SHIFT * 2))); 
        } 
        else 
        { 
            /* Set P0[7] to GPIO interrupt falling-edge trigger. 
            Pin_Button_SHIFT is multiplied by 2 as two bits of the interrupt configuration 
            register sets the configuration for one pin */ 
            CY_SET_REG32(Pin_Button__INTCFG, regVal | (FALLING_EDGE << (Pin_Button_SHIFT * 2))); 
        } 
        /* Toggle edgeFlag */ 
        edgeFlag ^= 0x01u; 
        
        /* Wait for Interrupt */ 
        while(!(CY_GET_REG32(Pin_Button__INTSTAT) & (0x01u << Pin_Button_SHIFT))) 
        {
            ;
        } 
        /* Clear interrupt */ 
        CY_SET_REG32(Pin_Button__INTSTAT, (0x01u << Pin_Button_SHIFT)); 
        /* Toggle LED */ 
        Pin_LED_Write(~Pin_LED_Read()); 
    } 
}

/* [] END OF FILE */
