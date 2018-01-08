/**
  DSM Generated Driver API Header File

*/


#ifndef _DSM_H
#define _DSM_H

/**
  Section: Included Files
*/

#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: DSM APIs
*/

/**
  @Summary
    Initializes the DSM

  @Description
    This routine configures the DSM specific control registers

  @Preconditions
    None

  @Returns
    None

  @Param
    None

  @Comment
    

  @Example
    <code>
    DSM_Initialize();
    </code>

*/
void DSM_Initialize(void);

/**
  @Summary
    Sets the MDBIT high

  @Description
    This API sets the MDBIT high, so modulator uses carrier high signal

  @Preconditions
    DSM_Initialize() function should have been called before calling this function

  @Returns
    None

  @Param
    None

  @Example
    <code>
    DSM_Initialize();
    DSM_ManualModulationSet();
    </code>

*/
void DSM_ManualModulationSet (void);

/**
  @Summary
    Sets the MDBIT low

  @Description
    This API sets the MDBIT low, so modulator uses carrier low signal

  @Preconditions
    DSM_Initialize() function should have been called before calling this function

  @Returns
    None

  @Param
    None

  @Example
    <code>
    DSM_Initialize();
    DSM_ManualModulationClear();
    </code>

*/
void DSM_ManualModulationClear (void);
/**
  @Summary
    Toggles the MDBIT

  @Description
    This API toggles the MDBIT

  @Preconditions
    DSM_Initialize() function should have been called 
	before calling this function

  @Returns
    None

  @Param
    None

  @Example
    <code>
    DSM_Initialize();
    DSM_ManualModulationToggle();
    </code>
*/
void DSM_ManualModulationToggle (void);

/**
  @Summary
    Enables modulation

  @Description
    This API enables the modulator.

  @Preconditions
    DSM_Initialize() function should have been called 
	before calling this function

  @Returns
    None

  @Param
    None

  @Example
    <code>
    DSM_Initialize();
    DSM_ModulationStart();
    </code>
*/
void DSM_ModulationStart (void);

/**
  @Summary
    Disables modulation

  @Description
    This API disables the modulator.

  @Preconditions
    DSM_Initialize() and DSM_ModulationStart()
	functions should have been called before calling this function

  @Returns
    None

  @Param
    None

  @Example
    <code>
    DSM_Initialize();
    DSM_ModulationStart();
    ...
    DSM_ModulationStop();
    </code>
*/
void DSM_ModulationStop (void);

/**
  @Summary
    Enables modulation pin output.

  @Description
    This API sends the modulator output on the MDOUT pin.

  @Preconditions
    DSM_Initialize() and DSM_ModulationStart() 
	functions should have been called before calling this function

  @Returns
    None

  @Param
    None

  @Example
    <code>
    DSM_Initialize();
    DSM_ModulationStart();
    DSM_ModulatorOutputEnable();
    </code>
*/
void DSM_ModulatorOutputEnable (void);

/**
  @Summary
    Disables modulation pin output.

  @Description
    This API stops sending the modulator output on the MDOUT pin.

  @Preconditions
    DSM_Initialize(), DSM_ModulatorOutputEnable() and DSM_ModulationStart() 
	functions should have been called before calling this function

  @Returns
    None

  @Param
    None

  @Example
    <code>
    DSM_Initialize();
    DSM_ModulationStart();
    DSM_ModulatorOutputEnable();
    ...
    DSM_ModulatorOutputDisable();
    </code>
*/
void DSM_ModulatorOutputDisable (void);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // _DSM_H
/**
 End of File
*/
