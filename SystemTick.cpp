#include "SystemTick.h"


void Initialize_SystemTick()
{
    SysTick->LOAD = SystemCoreClock / 1000; // 1ms se xay ra 1 ngat
    
    /* Disable Interrupt & Select Core Clock & Enable SysTick  */
    SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

}