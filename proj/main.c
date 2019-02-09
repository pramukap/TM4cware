#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/pll.h"
//#include "inc/pll.h"

//#include "inc/hw_types.h"
//#include "inc/hw_memmap.h"
//#include "driverlib/sysctl.h"
//#include "driverlib/gpio.h"


//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void __error__(char *pcFilename, uint32_t ui32Line) {
}
#endif

void Heartbeat_Init (void) {
	SYSCTL_RCGCGPIO_R |= 0x20;
	while ((SYSCTL_RCGCGPIO_R | 0x20) == 0);	
	
	GPIO_PORTF_AFSEL_R &= ~0x0E;
	GPIO_PORTF_AMSEL_R &= ~0x0E; 
	GPIO_PORTF_DEN_R |= 0x0E;
	GPIO_PORTF_DIR_R |= 0x0E; 
	GPIO_PORTF_DATA_R &= ~0x0E;
}

int main (void) {
	PLL_Init (Bus80_000MHz);	
	Heartbeat_Init();
	
	while (1) {
		GPIO_PORTF_DATA_R ^= 0x0E;

		for (int i = 0; i < 10000000; i++) {
			__asm__("");	//prevents delay loop from being optimized out
		}
	}
}
