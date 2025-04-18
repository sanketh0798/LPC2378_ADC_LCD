#include <stdio.h>
#include <LPC23xx.H>                    /* LPC23xx definitions                */
#include "LCD.h"                        /* Graphic LCD function prototypes    */

int adcdata;
float voltage;

void delay(void)
{
    unsigned int i, j;
    for(i=0; i<1000; i++)
        for(j=0; j<1000; j++);
}

__attribute__((section("RESET"))) //explicitly mentioning reset to solve the error when linker could not find RESET from .sct file.

int main()
{
	unsigned char buffer[20];
	
	lcd_init();
	lcd_clear();
	
	set_cursor(0, 0);
	lcd_print ("2024ht01603");// Display fixed string on 1st row (line=0), starting at column=0
		
	PCONP |= (1<<12);// Power on ADC
	
	PINSEL1 &= ~(0x3<<14); // Clear bits 15:14 for P0.23
  PINSEL1 |= (0X1<<14);	 // Set bits 15:14 to 01 for AD0.0
	
	//AD0INTEN |= (1 << 0);  // Enable interrupt for ADC channel 0 (AD0.0)

	AD0CR &= ~(1 << 0);    // Clear SEL0 (deselect AD0.0)
	AD0CR |= (1 << 0);     // Set SEL1 (select AD0.0)
	AD0CR |= (1 << 9);     // Set CLKDIV bit 1 (clock divider = 3)
	AD0CR |= (1 << 16);    // BURST = 0 (Software controlled conversion)
	AD0CR |= (1 << 21);    // Power up ADC (PDN = 1)
	AD0CR |= (1 << 24);  // Start conversion
	//AD0CR &= ~(0x7 << 24);    // Start bits = 000 (no start)
	
	
	while(1)
	{
//		AD0CR &= ~(0x7 << 24);  // **Clear start bits before initiating conversion**
//    AD0CR |= (1 << 24);     // **Start ADC conversion**
		
		while (!(AD0STAT & (1 << 0))); // 1st bit of ADOSTAT holds the DONE status for AD0.0. Wait until ADC conversion on channel 1 completes
			
			adcdata = (AD0DR0 & 0x0000FFC0); //the ADC's 1st channel register value is masked with 0x0000FFC0 which isolates bits 6 to 15 (binary 1111 1111 1100 0000)
			adcdata = adcdata >> 6; //Right-shift the result to align the 10-bit ADC value to the LSB since bit 6-15 of AD0DR1 holds the raw val.
			voltage = ((adcdata/1024.0f)*3.3f);
		
				// Prepare string to display voltage and date (16/4)
        // Format: "V=1.23V Date18/4"
        sprintf((char *)buffer, "V=%.2fV Date18/4", voltage);

        // Display on second row (line=1), column=0
        set_cursor(0, 1);

//        // Clear second line by printing spaces (optional)
//        lcd_print((unsigned char *)"                ");

//        // Set cursor again after clearing
//        set_cursor(0, 1);

        lcd_print(buffer);
		
			delay();
	}
	return 0;
}
