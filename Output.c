//
//  Output.c
//
//
//  Created by Leon Michael Mitchel Pearce on 25/09/2014.
//
//

#include "Output.h"

//-------------------------------LCD Functions-------------------------------------

/* Initialise the LCD with the desired settings. Must be done
 * in every program before using the LCD.
 *
 * - contrast: Contrast for the display (use 1 of the 3 constants defined in LCD.h)
 */
void Init_LCD(unsigned char contrast) {
    // Configure all of the pins correctly
    SET_OUTPUT(DDRD, SCEPIN);
    SET_OUTPUT(DDRB, RSTPIN);
    SET_OUTPUT(DDRB, DCPIN);
    SET_OUTPUT(DDRB, DINPIN);
    SET_OUTPUT(DDRF, SCKPIN);
    
    // Reset the screen
    OUTPUT_LOW(PORTB, RSTPIN);
    OUTPUT_HIGH(PORTD, SCEPIN);
    OUTPUT_HIGH(PORTB, RSTPIN);
    
    // Send configuration commands to the screen
    LCD_Write(LCD_COMMAND, 0x21);                       // Enable LCD extended command set
    LCD_Write(LCD_COMMAND, SET_CONTRAST | contrast ); 	// Set LCD Vop (Contrast)
    LCD_Write(LCD_COMMAND, 0x04);
    LCD_Write(LCD_COMMAND, 0x14);                       // LCD bias mode 1:48
    
    LCD_Write(LCD_COMMAND, 0x0C);                       // LCD in normal mode.
    LCD_Write(LCD_COMMAND, 0x20);                       // Enable LCD basic command set
    LCD_Write(LCD_COMMAND, 0x0C);
    
    LCD_Write(LCD_COMMAND, SET_ROW);                    // Reset row to 0
    LCD_Write(LCD_COMMAND, SET_COLUMN);                 // Reset column to 0
    
    //Clear LCD ram
    LCD_Clear();
}

/* Function writes a byte to the LCD (uses "bit bashing")
 * - dc: will interpret the byte as a command if dc = 0, as data if dc = 1
 * - data: the byte to be written to the LCD
 */
void LCD_Write(unsigned char dc, unsigned char data) {
	// Set the DC pin based on the parameter 'dc'
	OUTPUT_WRITE(PORTB,DCPIN,dc);
	
	// Pull the SCE/SS pin low to signal to the LCD we have data
	OUTPUT_LOW(PORTD,SCEPIN);
	
	// Write the byte of data using "bit bashing"
	int i;
	for(i = 7; i >= 0; i--) {
		OUTPUT_LOW(PORTF, SCKPIN) ;
		if(data>>i & 1 == 1) {
			OUTPUT_HIGH(PORTB, DINPIN);
		} else {
			OUTPUT_LOW(PORTB, DINPIN);
		}
		OUTPUT_HIGH(PORTF, SCKPIN);
	}
	
	// Pull SCE/SS high to signal the LCD we are done
	OUTPUT_HIGH(PORTD,SCEPIN);
}

/* Clears the LCD ram
 */
void LCD_Clear(void) {
	int index;
	
	for(index = 0; index <= LCD_WIDTH * (LCD_HEIGHT / WRITE_HEIGHT); index++){
	
		LCD_Write(LCD_DATA, WRITE_EMPTY);
	
	}
}

/* Sets the position of LCD cursor
 * - column: the new column for the cursor
 * - row: the new row for the cursor
 */
void LCD_Pos(unsigned char column, unsigned char row) {
    
    //write coordinates
    LCD_Write(LCD_COMMAND, SET_COLUMN | column);
    LCD_Write(LCD_COMMAND, SET_ROW | row);
    
    
}

//LCD Text Functions

/* Writes a character to the screen
 * - character: the chaaracter to write
 */
void LCD_Char(unsigned char character) {
	
    //variables
	int i = 0;
    
	//write char space
	LCD_Write(LCD_DATA, WRITE_EMPTY);
	
    //Write Char
	for(i = 0; i < 5; i++)
		LCD_Write(LCD_DATA, ASCII[character - 0x20][i]);

	//write char space
	LCD_Write(LCD_DATA, WRITE_EMPTY);
    
}

/* Writes string to the screen
 * - string: the string to write
 */
void LCD_String(unsigned char *string) {
    
    //Variables
    int i = 0;
    int j = 0;
    
    //loop for string
    while(string[j] != '\0'){
        
        LCD_Char(string[j]);
        
        j++;
        
    }
    
}

//-----------------------------LED Functions---------------------------------------

// initialises both leds
void Init_LED(){
    
    // changes led directional registers to high (outputs)
    DDRB |= (1 << DDB2) | (1 << DDB3);
    
}


// turns on led0
void LED0_On(){
    
    // sets led port high (led on)
    PORTB |= (1 << PORTB2);
    
}
// turns on led1
void LED1_On(){
    
    // sets led port high (led on)
    PORTB |= (1 << PORTB3);
    
}


// turns off led0
void LED0_Off(){
    
    // sets led port low (led off)
    PORTB &= ~(1 << PORTB2);
    
}
// turns off led1
void LED1_Off(){
    
    // sets led port low (led off)
    PORTB &= ~(1 << PORTB3);
    
}


// toggle led0
void LED0_Toggle(){
    
    // sets led port high (led on)
    PORTB ^= (1 << PORTB2);
    
}
// toggle led1
void LED1_Toggle(){
    
    // sets led port low (led off)
    PORTB ^= (1 << PORTB3);
    
}