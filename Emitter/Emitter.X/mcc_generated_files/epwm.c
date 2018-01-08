/**
  ECCP Generated Driver File


*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "epwm.h"

/**
  Section: Macro Declarations
*/

#define PWM_INITIALIZE_DUTY_VALUE    209

/**
  Section: EPWM Module APIs
*/

void EPWM_Initialize (void)
{
    // Set the PWM to the options selected in MPLAB(c) Code Configurator
    
    // CCP1M P1A: active high; P1B: active high; DC1B 1; P1M single; 
    CCP1CON = 0x1C;
    
    // CCP1ASE operating; PSS1BD low; PSS1AC low; CCP1AS disabled; 
    ECCP1AS = 0x00;
    
    // P1RSEN automatic_restart; P1DC 25; 
    PWM1CON = 0x99;
    
    // STR1B P1B_to_port; STR1A P1A_to_CCP1M; STR1SYNC start_at_next; 
    PSTR1CON = 0x11;
    
    // CCPR1L 52; 
    CCPR1L = 0x34;
    
    // CCPR1H 0; 
    CCPR1H = 0x00;
    
}

void EPWM_LoadDutyValue(uint16_t dutyValue)
{
   // Writing to 8 MSBs of pwm duty cycle in CCPRL register
    CCPR1L = ((dutyValue & 0x03FC)>>2);
    
   // Writing to 2 LSBs of pwm duty cycle in CCPCON register
    CCP1CON = (CCP1CON & 0xCF) | ((dutyValue & 0x0003)<<4);
}
/**
 End of File
*/
