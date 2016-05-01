//
//  Input.h
//  
//
//  Created by Leon Michael Mitchel Pearce on 25/09/2014.
//
//

#ifndef ____BTN__
#define ____BTN__

//-----------------------Libraries-------------------------

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
//-----------------------Definitions-----------------------

#define DEPRESSED   0
#define PRESSED     1
#define RELEASED    2

//-----------------------Functions-------------------------

//Initialises both btns
void Init_Input();
//Checks if btn0 is high (pressed) or low (depressed)
int BTN0_State();
//Checks if btn1 is high (pressed) or low (depressed)
int BTN1_State();
//Checks for btn0 release
int BTN0_Release();
//Checks for btn1 release
int BTN1_Release();
//Checks POT1 state
void POT1_Val();
//Returns wind_speed
int Wind_Speed_Val();
//ISR for ADC
ISR(ADC_vect);




#endif /* defined(____BTN__) */
