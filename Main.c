//
//  main.c
//  
//
//  Created by Leon Michael Mitchel Pearce on 29/09/2014.
//
//

#include "Main.h"

// The main initialises all hardware and acts as the navigation between game and menu/splash screens
int main(){
    
    //Variables
    char screen = MENU;
    
    //Initialise IO
    Init_IO();
    
    //Main loop
    while(1){
        
        if(screen == MENU){
            screen = Menu();
        }
        
        if(screen == GAME){
           screen = Game();
        }
        
        if (screen == WIN){
            screen = Win();
        }
        
        if (screen == LOSE){
            screen = Lose();
        }
        
    }
    
}

void Init_IO(){

    Init_LCD(LCD_HIGH_CONTRAST);
    Init_LED();
    Init_Input();

}



