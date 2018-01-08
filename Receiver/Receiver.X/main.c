/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15.1
        Device            :  PIC16F1829
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "mcc_generated_files/mcc.h"
#include "LCD_I2C_PCF8574.h"

volatile uint16_t dimmLevel = 3600;
volatile uint8_t outputStatus = 0;
volatile uint8_t nStatus = 0;
volatile uint16_t SecTimer = 0;

void TMR1_Routine(void){
    // add your TMR1 interrupt custom code
    // or set custom function using TMR1_SetInterruptHandler()
    if(outputStatus)
    {
        outputStatus = 0;
        TMR1_WriteTimer(65535 - (4000 - dimmLevel));
        IO_RC3_SetLow();
    }
    else
    {
        outputStatus = 1;
        if(dimmLevel == 0)
        {
            TMR1_WriteTimer(65535 - dimmLevel);
            IO_RC3_SetLow();
        }
        else
        {
            TMR1_WriteTimer(65535 - dimmLevel);
            IO_RC3_SetHigh();
        }
    }
}


/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    // Enable Timer1 interrupt for LED PWM
    TMR1_SetInterruptHandler(TMR1_Routine);
    
    /**/
    __delay_ms(2000);
    
    // Display first Logo Screen
    LCD_Init();
    LCDclear();
    LCDsetCursor(0, 0);
    LCD_Write_Str("   PIC16F1829   ");
    LCDsetCursor(0, 1);
    LCD_Write_Str("Receiver Ver 1.0");
    __delay_ms(4000);
    LCDclear();

    // Display second Logo Screen
    LCDsetCursor(0, 0);
    LCD_Write_Str("  Developed By  ");
    LCDsetCursor(0, 1);
    LCD_Write_Str("Jinzhouyun201705");
    __delay_ms(4000);
    LCDclear();
    
    uint8_t ChrIdx = 0;

    while (1)
    {
        // check UART from IR receiver
        if(EUSART_DataReady)
        {
            uint8_t nCommand = EUSART_Read();
            // Process LED command 
            if(nCommand >= '0' && nCommand <= '9')
                dimmLevel = 400 * (nCommand - '0');
            EUSART_Write(nCommand);
            
            // Check Character 
            if(((nCommand >= 'a' && nCommand <= 'z') || (nCommand >= 'A' && nCommand <= 'Z')) ||
                    ((nCommand >= '0' && nCommand <= '9') || (nCommand >= '!' && nCommand <= ')')))
            {
                // Display Command char on LCD, Process screen row
                if(ChrIdx < 16)
                {
                    LCDsetCursor(ChrIdx, 0);
                    LCD_Write_Char(nCommand);
                }
                else if(ChrIdx < 32)
                {
                    LCDsetCursor(ChrIdx % 16, 1);
                    LCD_Write_Char(nCommand);
                }
                else if(ChrIdx == 32)
                {
                    LCDclear();
                    ChrIdx = 0;
                    LCDsetCursor(0, ChrIdx);
                    LCD_Write_Char(nCommand);
                }
                ChrIdx++;
            }
        }
    }
}
/**
 End of File
*/