//
//  Objects.c
//  
//
//  Created by Leon Michael Mitchel Pearce on 1/10/2014.
//
//

#include "Objects.h"

struct Terrain New_Terrain(){
    
    //create new terrain
    struct Terrain new_terrain;
    
    //set terrain properties
    new_terrain.width = TERRAIN_WIDTH;
    new_terrain.height = TERRAIN_HEIGHT;
    
    //return struct terrain
    return new_terrain;
    
}

struct Tank New_Tank(struct Terrain terrain, char direction){
    
    struct Tank new_tank;
    
    //const properties
    new_tank.height = TANK_HEIGHT;
    new_tank.width = TANK_WIDTH;
    new_tank.direction = direction;
    
    new_tank.y = terrain.height + new_tank.height;
    if(direction == FACING_RIGHT){
        new_tank.x = 5;
    }else{
        new_tank.x = terrain.width - new_tank.width - 5;
    }
    
    
    
    return new_tank;
    
}

struct Turret New_Turret(struct Tank tank){
    
    struct Turret new_turret;
    
    new_turret.length = 5;
    new_turret.angle = 10;
    new_turret.power = 10;
    
    new_turret.x = tank.x + (tank.width / 2);
    new_turret.y = tank.y;
    new_turret.direction = tank.direction;
    
    //testing code
    new_turret.x2 = tank.x + (tank.width / 2) + new_turret.length;
    new_turret.y2 = tank.y;
    
    return new_turret;
    
}

struct Power_Bar New_Power_Bar(struct Turret turret){
    
    struct Power_Bar new_power_bar;
    
    new_power_bar.label = "Power";
    new_power_bar.power = turret.power;
    new_power_bar.x = 0;
    new_power_bar.y = 8;
    
    return new_power_bar;
    
}

struct Bullet New_Bullet(struct Turret turret){
    
    struct Bullet new_bullet;
    
    new_bullet.height = BULLET_HEIGHT;
    new_bullet.width = BULLET_WIDTH;
    new_bullet.weight = BULLET_WEIGHT;
    
    new_bullet.direction = turret.direction;
    new_bullet.power = turret.power;
    new_bullet.angle = turret.angle;
    new_bullet.y = turret.y2;
    
    if(new_bullet.direction == FACING_RIGHT){
        new_bullet.x = turret.x2;
    }else{
        new_bullet.x = turret.x2 - (BULLET_WIDTH + 1);
    }
    
    return new_bullet;
    
}

struct Wind_Bar New_Wind_Bar(){
    
    struct Wind_Bar wind_bar;
    
    wind_bar.x = 0;
    wind_bar.y = 0;
    
    wind_bar.label = "WIND";
    
    return wind_bar;
    
}