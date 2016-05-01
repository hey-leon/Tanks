//
//  Input.c
//  
//
//  Created by Leon Michael Mitchel Pearce on 25/09/2014.
//
//

#include "Input.h"


//Initialises both btns and pot/adc
void Init_Input(){
    
    // changes btn directional registers to low (inputs)
    DDRB &= ~((1 << DDB0)|(1 << DDB1));
    
    
    // Configure ADC0 (POT1)
    ADMUX |= 0b01100000; // REFS7:6 = 01 = AVCC as reference,
                         // ADLAR5 = 1 = Left adjust
                         // MUX4:0  0000 = ADC0 = PORTF0 = POT1
    
    ADCSRA = 0b10001100; // ADEN7 = 1: enable ADC,
                         // ADSC6 = 0: don't start conversion yet
                         // ADATE5 = 0: disable auto trigger,
                         // ADIE3 = 1: enable ADC interrupt
                         // ASPS2:0 = 100 = 16 prescaler
    
    
    // initialises teensy global interrupts
    sei();

    
}

//---------------------------Button Functions-------------------------------

//Checks if btn0 is high (pressed) or low (depressed)
//Returns 1 if pressed, -1 if depressed.
int BTN0_State(){
    
    // check if PINB0 (btn0) is high
    if((PINB >> PINB0) & (1 << 0) == PRESSED){
        _delay_ms(50);
        //double check if PINB0 (btn0) is high (for bouncing)
        if((PINB >> PINB0) & (1 << 0) == PRESSED){
            //btn0 is pressed
            return PRESSED;
        }
    }
    // btn0 is depressed
    return DEPRESSED;
}

//Checks if btn1 is high (pressed) or low (depressed)
//Returns PRESSED if pressed, DEPRESSED if depressed.
int BTN1_State(){
    
    // check if PINB1 (btn1) is high
    if((PINB >> PINB1) & (1 << 0) == PRESSED){
        _delay_ms(50);
        //double check if PINB1 (btn1) is high (for bouncing)
        if((PINB >> PINB1) & (1 << 0) == PRESSED){
            //btn0 is pressed
            return PRESSED;
        }
    }
    // btn0 is depressed
    return DEPRESSED;
}

//Checks for btn0 release
//Returns RELEASED on release, else 0.
int BTN0_Release(){
    //Remembers btn0 state
    static char current_state = DEPRESSED;
    
    //If current state is depressed checks btn0 state
    if(current_state == DEPRESSED && BTN0_State() == PRESSED){
        //Button is pressed
        current_state = PRESSED;
    }
    
    //If current state is pressed checks btn0 state
    if(current_state == PRESSED && BTN0_State() == DEPRESSED){
        //Button has just been released
        current_state = DEPRESSED;
        //Return Released!!!
        return RELEASED;
    }
    
}

//Checks for btn0 release
//Returns RELEASED on release, else 0.
int BTN1_Release(){
    //Remembers btn0 state
    static char current_state = DEPRESSED;
    
    //If current state is depressed checks btn0 state
    if(current_state == DEPRESSED && BTN1_State() == PRESSED){
        //Button is pressed
        current_state = PRESSED;
    }
    
    //If current state is pressed checks btn0 state
    if(current_state == PRESSED && BTN1_State() == DEPRESSED){
        //Button has just been released
        current_state = DEPRESSED;
        //Return Released!!!
        return RELEASED;
    }
    
}

//---------------------------Pot/ADC Functions------------------------------

//variables
int wind_speed = 0;

//POT1 ISR
//Returns a value to wind_speed between -45 and 45 (slight bias for 0)
ISR(ADC_vect){
    
    wind_speed = -((ADCH - 128) / 12.8);
    if(wind_speed > 0)
        wind_speed -= 1;
    wind_speed *= 5;
    
}

//Initiates POT1 value check
void POT1_Val(){
    
    ADCSRA |= (1 << ADSC);
    
}

//Returns wind speed
int Wind_Speed_Val(){
    
    return wind_speed;
    
}




