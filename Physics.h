//
//  Physics.h
//  
//
//  Created by Leon Michael Mitchel Pearce on 1/10/2014.
//
//

#ifndef ____Physics__
#define ____Physics__

//-------------------Libraries---------------------

#include <avr/io.h>
#include <math.h>

#include "Objects.h"
#include "Graphics.h"

//------------------Definitions--------------------

#define GRAVITY 19.6f
#define MAX_KINETIC 1100

//collisions
#define IN_FLIGHT  -1
#define HIT_TANK    1
#define HIT_SELF    2
#define HIT_SHORT   3
#define HIT_LONG    4


//------------------Definitions--------------------

void Calc_Vel_Init(struct Bullet* bullet);

void Calc_Vel_Change(struct Bullet* bullet, int wind_speed, int delay);

void Calc_Motion(struct Bullet* bullet, int delay);

int Detect_Collision(struct Bullet bullet, struct Tank tank, struct Tank self, struct Terrain terrain);\

void Calc_Kill_Ratio(int power, int angle, int weight, float* x_vel, float* y_vel);

int Validate_Kill_Ratio(float x_vel, float y_vel, int wind_speed, int distance);

#endif /* defined(____Physics__) */
