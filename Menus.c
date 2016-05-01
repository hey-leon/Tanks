//
//  Menus.c
//  
//
//  Created by Leon Michael Mitchel Pearce on 25/09/2014.
//
//

#include "Menus.h"


// menu program
int Menu(){

    //variables
    char seed_count;
    
    // show splash
    Show_Splash();
    
    //Initialise rand seed timer
    Init_Rand();
    
    //Menu Loop
    while(1){
        
        //check for timer count
        if ((TIFR0 >> TOV0) & 1 == 1){
            seed_count++;
            TIFR0 |= 1 << TOV0;
        }

        if(BTN0_Release() == RELEASED){
            srand(seed_count);
            Count_Down();
            return GAME;
        }
        
        if(BTN1_Release() == RELEASED){
            srand(seed_count);
            Count_Down();
            return GAME;
        }
        
    }
    
}
// menu helpers
void Show_Splash(){
    
    //Strings
    char* title = "Scorched!";
    char* ID = "n9146890";
    char* name = "Leon Pearce";
    
    //Clear LCD
    LCD_Clear();

    //Show title
    LCD_Pos((LCD_WIDTH/ 2) - ((strlen(title) / 2) * CHAR_WIDTH), ROW1);
    LCD_String(title);
    
    //Show student ID
    LCD_Pos((LCD_WIDTH/ 2) - ((strlen(ID) / 2) * CHAR_WIDTH), ROW3);
    LCD_String(ID);
    
    //Show name
    LCD_Pos((LCD_WIDTH/ 2) - ((strlen(name) / 2) * CHAR_WIDTH), ROW4);
    LCD_String(name);
    
}
void Count_Down(){
    //Variables
    char i;
    
    //Clear LCD
    LCD_Clear();
    
    //Loop for countdown
    for(i = 3; i > 0; i--){
        //Move lcd cursor
        LCD_Pos((LCD_WIDTH / 2) - CHAR_WIDTH / 2, ROW2);
        //Print i
        LCD_Char(CONVERT_TO_CHAR(i));
        //Wait 1 second
        _delay_ms(500);
        
    }
    
}
void Init_Rand(){
    
    //set to normal (default register values)
    
    //set prescale to 1024
    TCCR0B |= (1 << CS02) | (1 << CS00);
    
}

//result screens
int Win(){
    
    //variables
    char* Result = "Player Win!";

    
    //Clear LCD
    LCD_Clear();
    
    //Show result
    LCD_Pos((LCD_WIDTH/ 2) - ((strlen(Result) / 2) * CHAR_WIDTH), ROW2);
    LCD_String(Result);
    
    //program loop
    while(1){
        
        //led flash
        {
            _delay_ms(50);
            LED0_Toggle();
            LED1_Toggle();
        }
        
        //check button state
        {
            if(BTN0_Release() == RELEASED){
                LED0_Off();
                LED1_Off();
                return MENU;
            }
            
            if(BTN1_Release() == RELEASED){
                LCD_Clear();
                LED0_Off();
                LED1_Off();
                return MENU;
            }
        }
        
    }
    
    
}
int Lose(){
    
    //variables
    char* Result = "Player Lose!";
    
    //Clear LCD
    LCD_Clear();
    
    //Show result
    LCD_Pos((LCD_WIDTH/ 2) - ((strlen(Result) / 2) * CHAR_WIDTH), ROW2);
    LCD_String(Result);
    
    
    //program loop
    while(1){
        
        //Led Flash
        {
            _delay_ms(50);
                LED0_Toggle();
                LED1_Toggle();
        }
        
        //button state checks
        {
            if(BTN0_Release() == RELEASED){
                LCD_Clear();
                LED0_Off();
                LED1_Off();
                return MENU;
            }
            
            
            if(BTN1_Release() == RELEASED){
                LCD_Clear();
                LED0_Off();
                LED1_Off();
                return MENU;
            }
        }
        
    }
    
    
}




