//
//  Objects.h
//  
//
//  Created by Leon Michael Mitchel Pearce on 1/10/2014.
//
//

#ifndef _Objects_h
#define _Objects_h

//----------------Structures------------------

struct Terrain {
    
    char height;
    char width;
    
};

struct Turret {
    
    char length;
    char angle;
    char x;
    char y;
    char x2;
    char y2;
    char direction;
    char power;
    
    
};

struct Tank {
    
    char x;
    char y;
    char width;
    char height;
    char direction;
    
};

struct Power_Bar {
    
    char* label;
    char power;
    char x;
    char y;
    
};

struct Wind_Bar {
    
    char* label;
    
    int x;
    int y;
    
    int wind_speed;
};

struct Bullet {
    
    char height;
    char width;
    char weight;
    
    char direction;
    char power;
    char angle;
    float x;
    float y;
    
    double x_vel;
    double y_vel;
    
};


//----------------Definitions-----------------

//Direction Definitions
#define FACING_RIGHT    1
#define FACING_LEFT     (-1)

//Terrain Definitions
#define TERRAIN_WIDTH   84
#define TERRAIN_HEIGHT  5

//Tank Definitions
#define TANK_WIDTH   5
#define TANK_HEIGHT  3

//Bullet Definitions
#define BULLET_WIDTH   2
#define BULLET_HEIGHT  2
#define BULLET_WEIGHT    20



//----------------Functions-------------------

struct Terrain New_Terrain();

struct Tank New_Tank(struct Terrain terrain, char direction);

struct Turret New_Turret(struct Tank tank);

struct Power_Bar New_Power_Bar(struct Turret turret);

struct Bullet New_Bullet(struct Turret turret);

struct Wind_Bar New_Wind_Bar();

#define BAR_EDGE    129
#define BAR_FILL    255


#endif
