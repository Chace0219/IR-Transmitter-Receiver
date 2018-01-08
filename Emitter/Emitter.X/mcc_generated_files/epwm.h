/**
  ECCP Generated Driver File

*/

#ifndef _EPWM_H
#define _EPWM_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: EPWM Module APIs
*/

  /**
  @Summary
    Initializes the EPWM

  @Description
    This routine initializes the EPWM_Initialize.
    This routine must be called before any other ECCP routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    

 @Example
    <code>
    uint16_t dutycycle;

    EPWM_Initialize();
    EPWM_LoadDutyValue(dutycycle);
    </code>
 */
void EPWM_Initialize(void);

/**
  @Summary
    Loads 16-bit duty cycle.

  @Description
    This routine loads the 16 bit duty cycle value.

  @Preconditions
    EPWM_Initialize() function should have been called before calling this function.

  @Param
    Pass in 16bit duty cycle value.

  @Returns
    None

  @Example
    <code>
    uint16_t dutycycle;

    EPWM_Initialize();
    EPWM_LoadDutyValue(dutycycle);
    </code>
*/
void EPWM_LoadDutyValue(uint16_t dutyValue);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // _EPWM_H
/**
 End of File
*/
