//
//  game.h
//  
//
//  Created by Leon Michael Mitchel Pearce on 1/10/2014.
//
//

#ifndef ____game__
#define ____game__

//------------------------LIBRARIES-------------------------

// standard avr libs
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// custom lib
#include "Input.h"
#include "Graphics.h"
#include "Objects.h"
#include "Physics.h"

//-----------------------Definitions------------------------

//program index
#define MENU    -1
#define GAME    1
#define WIN     2
#define LOSE    3

//collisions
#define IN_FLIGHT  -1
#define HIT_TANK    1
#define HIT_SELF    2
#define HIT_SHORT   3
#define HIT_LONG    4

//turn index
#define PLAYER_TURN -1
#define AI_TURN     1

//-----------------------PROTOTYPES-------------------------

int player_turn(struct Turret* player_turret);

void player_angle(struct Turret* player_turret);

void player_power(struct Turret* player_turret);

int ai_turn(struct Turret* ai_turret);

void ai_angle(struct Turret* ai_turret, int max_angle, int min_angle);

void ai_power(struct Turret* ai_turret, int max_power, int min_power);


int shot(struct Turret* turret, struct Tank enemy, struct Tank self);


void Draw_Statics();

//update wind bar
void Update_Wind();



#endif /* defined(____game__) */
