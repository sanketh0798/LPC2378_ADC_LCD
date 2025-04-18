# LPC2378_ADC_LCD
C program for displaying a fixed on the 1st Row and voltage difference between the terminals of the potentiometer, along with the date in the DD/M format, on the 2nd row of the LCD Display present in the LPC2378 kit. The Potentiometer is connected to the AD0.0 pin (P0.23) of LPC2378.

Actual program is written in LCD_Display.c

Use the lcd.h and lcd_4bits.c for LCD-related functions and definitions, respectively.

NOTE: While debugging, if your PC is getting stuck at either lcd_init() or set_cursor() or any other lcd functions, comment out the wait_while_busy() in lcd_write_data () and lcd_write_cmd().
The setup for the HW debugger in the Porject Option should be like - ![WhatsApp Image 2025-04-18 at 15 19 10_810a88a1](https://github.com/user-attachments/assets/87dcd8a6-e74c-4512-9405-f8a16f253712)

