#include "SystemTick.h"


void Initialize_SystemTick()
{
    /* Enable SysTick interrupt in NVIC level */
    NVIC_ClearPendingIRQ(SysTick_IRQn);	
    NVIC_EnableIRQ(SysTick_IRQn);
    SysTick->LOAD = SystemCoreClock / 100000;  // 1us
    /* Disable Interrupt & Select Core Clock & Enable SysTick  */
    SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

    
    //Ngoai ra co the dat muc uu tien ngat 
}