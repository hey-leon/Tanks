//
//  Output.h
//
//
//  Created by Leon Michael Mitchel Pearce on 25/09/2014.
//
//

#ifndef LCD_H_
#define LCD_H_

//---------------------Libraries-----------------------------------------------//

//standard avr libs
#include <avr/io.h>
#include <string.h>

//custom font libs
#include "ASCIIFont.h"

//---------------------Definitions---------------------------------------------//

// What pins on PORTB did we connect D/C and RST to
#define DCPIN		5 //PORTB
#define RSTPIN		4 //PORTB

// What PORTB pins are the DATA Communication lines on
#define DINPIN		6 // PORTB
#define SCKPIN		7 // PORTF
#define SCEPIN		7 // PORTD

// LCD DC
#define LCD_COMMAND		0
#define LCD_DATA		1

// LCD Comands
#define SET_COLUMN      128
#define SET_ROW         64
#define SET_CONTRAST    128

// LCD Command values
#define LCD_LOW_CONTRAST		0x2F
#define LCD_DEFAULT_CONTRAST	0x3F
#define LCD_HIGH_CONTRAST		0x4F

// Dimensions of the LCD Screen
#define LCD_WIDTH       84
#define LCD_HEIGHT      48
#define LCD_ROWS        6

// Row Defines
#define ROW0   0
#define ROW1   1
#define ROW2   2
#define ROW3   3
#define ROW4   4
#define ROW5   5

// Write Defines
#define WRITE_HEIGHT    8
#define WRITE_EMPTY     0

// CPU Frequency Defines
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_8MHz        0x01

// Helpful Macros
#define SET_INPUT(portdir, pin)			portdir &= ~(1 << pin) 
#define SET_OUTPUT(portdir, pin)		portdir |= (1 << pin)
#define OUTPUT_WRITE(port, pin, value)	port = (port & ~(1 << pin)) | (value << pin)
#define OUTPUT_LOW(port, pin)			port &= ~(1 << pin)
#define OUTPUT_HIGH(port, pin)			port |= (1 << pin)
#define READ_LINE(port, pin)			port & (1 << pin)
#define CONVERT_TO_CHAR(int)            int + 48


//--------------------- Prototypes------------------------------------------------------//

//----------------------LCD Functions----------------------//
void Init_LCD(unsigned char contrast);
void LCD_Write(unsigned char dc, unsigned char data);
void LCD_Clear(void);
void LCD_Pos(unsigned char column, unsigned char row);

// LCD Text functions
void LCD_Char(unsigned char character);
void LCD_String(unsigned char *string);

//---------------------LED Functions----------------------//
void Init_LED();

// turns on led0
void LED0_On();
// turns on led1
void LED1_On();
// turns off led0

void LED0_Off();
// turns off led1
void LED1_Off();

// toggle led0
void LED0_Toggle();
// toggle led1
void LED1_Toggle();



#endif /* LCD_H_ */