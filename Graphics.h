//
//  Graphics.h
//
//
//  Created by Leon Michael Mitchel Pearce on 27/09/2014.
//
//


#ifndef GRAPHICS_H_
#define GRAPHICS_H_

//----------------------------Libraries---------------------------------//

//standard avr libs
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

//custom libs
#include "Output.h"
#include "Objects.h"
#include "ASCIIFont.h"

//----------------------------Definitions-------------------------------//
 
//Screen buffer
extern unsigned char screen_buff[LCD_WIDTH][LCD_ROWS];

//----------------------------Functions---------------------------------//

//Graphics general functions
void Write_Buff(void);
void Clear_Buff(void);
void Draw_Pixel(unsigned char x, unsigned char y);
void Undraw_Pixel(unsigned char x, unsigned char y);
int Draw_Char(unsigned char character, int x, int y);
int Undraw_Char(unsigned char character, int x, int y);
int Draw_String(char* string, int x, int y);
int Undraw_String(char* string, int x, int y);
int Draw_int(int i, unsigned int places, int x, int y);
int Undraw_int(int i, unsigned int places, int x, int y);

//Draw Graphics
void Draw_Bullet(struct Bullet bullet);
void Draw_Tank(struct Tank tank);
void Draw_Turret(struct Turret* turret);
void Draw_Terrain(struct Terrain terrain);
void Draw_Power_Bar(struct Power_Bar power_bar);
void Draw_Wind_Bar(struct Wind_Bar wind_bar);

//Undraw Graphics
void Undraw_Bullet(struct Bullet bullet);
void Undraw_Turret(struct Turret* turret);
void Undraw_Power_Bar(struct Power_Bar power_bar);
void Undraw_Wind_Bar(struct Wind_Bar wind_bar);

//effects
void Explosion(int x, int y, int direction);


#endif /* GRAPHICS_H_ */