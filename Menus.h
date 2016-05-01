//
//  Menus.h
//
//
//  Created by Leon Michael Mitchel Pearce on 25/09/2014.
//
//

#ifndef ____main__
#define ____main__

//------------------------LIBRARIES-------------------------

// standard avr libs
#include <avr/io.h>
#include <util/delay.h>

// custom lib
#include "Input.h"
#include "Output.h"


//-----------------------Definitions------------------------

//program index
#define MENU    -1
#define GAME    1
#define WIN     2
#define LOSE    3

//-----------------------PROTOTYPES-------------------------

// Menu
int Menu();
// Menu helpers
void Show_Splash();
void Count_Down();
void Init_Rand();

// Win
int Win();

// Lose
int Lose();



#endif /* defined(____main__) */
