//
//  main.h
//  
//
//  Created by Leon Michael Mitchel Pearce on 29/09/2014.
//
//

#ifndef ____main__
#define ____main__

//----------------------------Libraries---------------------------------

//standard avr libs
#include <avr/io.h>

// custom libs
#include "Input.h"
#include "Output.h"

// programs
#include "Menus.h"

//----------------------------Definitions-------------------------------

//program index
#define MENU    -1
#define GAME    1
#define WIN     2
#define LOSE    3

//-----------------------------Functions--------------------------------

void Init_IO();

#endif /* defined(____main__) */
