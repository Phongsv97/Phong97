#include "uart.h"
#define OVER_SAMPLE 16
void uart0_init ( int sysclk, int baud)
{
  
	SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK );
        PORTA->PCR[1]= PORT_PCR_MUX(0x2);// Chuyen chan PAT1 sang che do uart
	PORTA->PCR[2]= PORT_PCR_MUX(0x2);// Chuyen chan PAT2 sang che do uart
	SIM->SOPT2 = (SIM->SOPT2 & ~SIM_SOPT2_UART0SRC_MASK) | SIM_SOPT2_UART0SRC(1); // Cau hinh tan so he thong
	SIM->SOPT2 = (SIM->SOPT2 & ~SIM_SOPT2_PLLFLLSEL_MASK) | SIM_SOPT2_PLLFLLSEL_MASK;//48/2 = 24
        
        
    uint32_t uart0clk;
    uint32_t baud_rate;
    
    SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
    
    // Disable UART0 before changing registers
    UART0->C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);
  
    // Initialize baud rate
    baud_rate = baud;
    
    // Change units to Hz
    uart0clk = sysclk * 1000;
    // Set the baud rate divisor
      uint16_t divisor = ( uart0clk / OVER_SAMPLE) / baud_rate;//312
      UART0->C4 = UART0_C4_OSR(OVER_SAMPLE - 1);
      UART0->BDH = (divisor >> 8) & UART0_BDH_SBR_MASK;
      UART0->BDL = (divisor & UART0_BDL_SBR_MASK);
    
      // Enable the transmitter, receiver 
      UART0->C2 = UART0_C2_RE_MASK | UART0_C2_TE_MASK ;
        		
    
}

char uart0_getchar ()
{
      /* Wait until character has been received */
      while (!(UART0->S1 & UART0_S1_RDRF_MASK));
    
      /* Return the 8-bit data from the receiver */
      return UART0->D;
}

unsigned short canT;
void uart0_putchar ( char ch)
{
      canT = (UART0->S1 & UART0_S1_TC_MASK) >> UART0_S1_TC_SHIFT;
      /* Wait until space is available in the FIFO */
      while(((UART0->S1 & UART0_S1_TC_MASK) >> UART0_S1_TC_SHIFT)==0);
    
      /* Send the character */
      UART0->D = (uint8_t)ch;
      
//      while(((UART0_S1 & UART0_S1_TC_MASK) >> UART0_S1_TC_SHIFT)==0);
   
 }

void USART0_putstr(char *str)
{
  while(*str)
  {
    if(*str == '\n')
    {
      uart0_putchar('\r');
    }
    uart0_putchar(*str++);
  }
}


