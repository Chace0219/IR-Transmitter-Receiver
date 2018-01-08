/**

*/

#include "mcc_generated_files/mcc.h"
#include "Software_UART.h"
/*
                         Main application
*/
/* Defines for SoftUart on RA5 */
typedef enum
{
    SOFTUART_IDLE,
    SOFTUART_START,
    SOFTUART_DATA,
    SOFTUART_STOP,

} Soft_UART_Status;

typedef struct
{
    uint8_t data;
    uint8_t bitIndex;
    bool dataReady;
    
} SoftUART_OBJECT;

static volatile Soft_UART_Status softUart = SOFTUART_IDLE;
static volatile SoftUART_OBJECT object;

/* Variables to control dimming level using Timer1 interrupt */
volatile uint16_t dimmLevel = 1500; // 
volatile uint8_t outputStatus = 0; // it presents current status of led driver pin

/* Timer 1 interrupt service routine */
void TMR1_Routine(void)
{ // so, we can output pwm for LED driving using TMR1 interrupt
    // 
    if(outputStatus)
    { // When output is HIGH
        // set Timer register as free cycle
        TMR1_WriteTimer(65535 - (4000 - dimmLevel));
        // Output LOW signal
        outputStatus = 0;
        IO_RA4_SetLow();
    }
    else
    { // When Output is LOW
        outputStatus = 1;
        if(dimmLevel == 0)
        { // If we set dimming level 0%, output RA4 pin as LOW
            TMR1_WriteTimer(65535 - dimmLevel);
            IO_RA4_SetLow();
        }
        else
        { // set Timer register as duty cycle
            TMR1_WriteTimer(65535 - dimmLevel);
            IO_RA4_SetHigh();
        }
    }
}

bool getSoftRX();
bool softUartReady();
uint8_t softUartRead();
void initSoftUart();


/* I am using Timer 0 interrupt in order to ensure 9600 baud rate for softuart */
void TMR0_CustomISR(void)
{
    // BUS IDLE Status
    if(softUart == SOFTUART_IDLE)
    {
        
        if(!getSoftRX())
        { //  if START SIGNAL is detected
            
            // 
            softUart = SOFTUART_START;
            // init softuart object  
            object.bitIndex = 0;
            object.dataReady = false;
            object.data = 0;
            
            // bit accepting status
            softUart = SOFTUART_DATA;
        }
    }
    else if(softUart == SOFTUART_DATA)
    { // BUS DATA accept, 
        if(getSoftRX())// if bit is 1, 
            object.data += 1 << object.bitIndex;
        object.bitIndex++;
        // 8 bits are received
        if(object.bitIndex > 7)
           softUart = SOFTUART_STOP; 
    }
    else if(softUart == SOFTUART_STOP)
    { // 
        if(getSoftRX())
        { // Stop bit okay
            object.dataReady = true;
            softUart = SOFTUART_IDLE;
        }
        else 
        { // Error
            object.dataReady = false;
            softUart = SOFTUART_IDLE;
        }
    }
}

/* Soft UART */
void initSoftUart()
{
    object.bitIndex = 0;
    object.data = 0;
    object.dataReady = false;
    TMR0_SetInterruptHandler(TMR0_CustomISR);
}

bool getSoftRX()
{
    if(IO_RA5_GetValue())
        return true;
    else
        return false;
}

bool softUartReady()
{
    return object.dataReady;
}

uint8_t softUartRead()
{
    object.dataReady = false;
    return object.data;
}

/* */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    TMR1_SetInterruptHandler(TMR1_Routine);
    
    // soft uart init
    initSoftUart();
    
    // DSM module init
    DSM_ModulationStart();
    
    while (1)
    {
        if(softUartReady())
        {
            uint8_t nCommand = softUartRead();
            if(nCommand  >= '0' && nCommand  <= '9')
                dimmLevel = (nCommand - 0x30) * 400;
            
            EUSART_Write(nCommand);
            // 
            //EUSART_Write(0xFF);
            //EUSART_Write(0xFF);
            //DSM_ModulationStop();            
        }
    }
}
/**
 End of File
*/