//
//  game.c
//  
//
//  Created by Leon Michael Mitchel Pearce on 1/10/2014.
//
//

#include "Game.h"

struct Terrain terrain;
struct Wind_Bar wind_bar;

struct Tank player_tank;
struct Tank ai_tank;
struct Turret player_turret;
struct Turret ai_turret;

//game program
int Game(){
    
    //Variables
    int result = -1;
    int turn = PLAYER_TURN;
    
    //initialise interrupt services
    sei();
    
    //Initialise objects
    terrain = New_Terrain();
    wind_bar = New_Wind_Bar();
    
    player_tank = New_Tank(terrain, FACING_RIGHT);
    player_turret = New_Turret(player_tank);
    ai_tank = New_Tank(terrain, FACING_LEFT);
    ai_turret = New_Turret(ai_tank);
    
    //Draw objects
    Draw_Statics();
    //update LCD
    Write_Buff();

    //Game Loop
    while(1){
        
        //Player turn
        if(turn == PLAYER_TURN){
            result = player_turn(&player_turret);
            //if game over
            if(result == HIT_TANK){
                //GAME WIN
                Clear_Buff();
                return WIN;
            }else if(result == HIT_SELF){
                //GAME LOSE
                Clear_Buff();
                return LOSE;
            }else{
                turn = AI_TURN;
            }
        }
        //AI TURN
        if(turn == AI_TURN){
            result = ai_turn(&ai_turret);
            //if game over
            if(result == HIT_TANK){
                //GAME LOSE
                Clear_Buff();
                return LOSE;
            }else if(result == HIT_SELF){
                //GAME WIN
                Clear_Buff();
                return WIN;
            }else{
                turn = PLAYER_TURN;
            }
        }
    }
}

//player turn
int player_turn(struct Turret* player_turret){
    char* notification = "PLAYER TURN!";
    int result = -1;
    
    //player turn notification
    Draw_String(notification, (LCD_WIDTH / 2)-(((strlen(notification) / 2) - 1)* CHAR_WIDTH), LCD_HEIGHT / 2);
    Write_Buff();
    _delay_ms(500);
    Undraw_String(notification, (LCD_WIDTH / 2)-(((strlen(notification) / 2) - 1)* CHAR_WIDTH), LCD_HEIGHT / 2);
    Write_Buff();
    
    //player inputs angle
    player_angle(player_turret);
    
    //select power
    player_power(player_turret);
    
    //players shot
    result = shot(player_turret, ai_tank, player_tank);
    
    return result;
    
}
//step one (user selects angle)
void player_angle(struct Turret* player_turret){
    
    while(1){
        //update LCD
        Write_Buff();
        
        //redraw wind bar
        Undraw_Wind_Bar(wind_bar);
        //sample adc
        POT1_Val();
        wind_bar.wind_speed = Wind_Speed_Val();
        //display adc
        Draw_Wind_Bar(wind_bar);

        //Btn0 released
        if(BTN0_Release() == RELEASED){
            //undraw turret
            Undraw_Turret(player_turret);
            //Increase angle
            player_turret->angle += 10;
            if(player_turret->angle > 80)
                player_turret->angle = 10;
            //draw turret
            Draw_Turret(player_turret);
        }
        
        if(BTN1_Release() == RELEASED){
            return;
        }
    }
    
}
//step two (user selects power)
void player_power(struct Turret* player_turret){
    
    //Initialise power bar
    struct Power_Bar power_bar = New_Power_Bar(*player_turret);
    //Draw power bar
    Draw_Power_Bar(power_bar);
    //update LCD
    Write_Buff();
    
    while(1){
        //update LCD
        Write_Buff();
        
        //redraw wind bar
        Undraw_Wind_Bar(wind_bar);
        //sample adc
        POT1_Val();
        wind_bar.wind_speed = Wind_Speed_Val();
        //display adc
        Draw_Wind_Bar(wind_bar);
        
        //Btn0 presssed
        if(BTN0_State() == PRESSED){
            // increase turret power
            player_turret->power += 2;
            power_bar.power = player_turret->power;
            
            // check if power maxed out
            if(player_turret->power > 100){
                //undraw full bar
                Undraw_Power_Bar(power_bar);
                //empty power
                player_turret->power = 10;
                power_bar.power = player_turret->power;
            }
            //Draw updated power bar
            Draw_Power_Bar(power_bar);
            //update LCD
            Write_Buff();
        }
        
        
        //btn1 pressed
        if(BTN1_Release() == RELEASED){
            //undraw power bar
            Undraw_Power_Bar(power_bar);
            //update LCD
            Write_Buff();
            return;
        }
        
    }
}



//ai turn
int ai_turn(struct Turret* ai_turret){
    int result = 0, rand_result = 0;
    static unsigned char hit_angle = 0, hit_power= 0;
    static int max_angle = 80, min_angle = 10;
    static int max_power = 100, min_power = 10;
    static char hit_bool = 0, turn = 5;
    
    {//ai turn notification
    char* notification = "ENEMY TURN!";
    Draw_String(notification, (LCD_WIDTH / 2)-(((strlen(notification) / 2) - .5)* CHAR_WIDTH), LCD_HEIGHT / 2);
    Write_Buff();
    _delay_ms(500);
    Undraw_String(notification, (LCD_WIDTH / 2)-(((strlen(notification) / 2) - .5)* CHAR_WIDTH), LCD_HEIGHT / 2);
        Write_Buff();}
    
    //optimum angle/power
        if(hit_bool == 0){
            float test_x, test_y, kill[1];
            int distance = 0;
            int  i = 0, j = 0;
            
            //calculate distance
            distance = ((ai_tank.x) - (player_tank.x + player_tank.width));
            
            // test shot
            for(i = 10; i <= 40; i += 10){
                for(j = 100; j >= 10; j -= 2){
                    
                    Calc_Kill_Ratio(j, i, 20, &test_x, &test_y);
                    
                    if(Validate_Kill_Ratio(test_x, test_y, wind_bar.wind_speed, distance) == 1){
                        hit_angle = i;
                        hit_power = j;
                        i = 50;
                        j = 0;
                        hit_bool = 1;
                    }
                    
                }
            }
            
            //angle/power range range
            min_angle = hit_angle - (20 + ((rand() % 1) * 10))  ;
            if(min_angle < 10)
                min_angle = 10;
            max_angle = hit_angle + (20  + ((rand() % 1) * 10));
            if(max_angle > 80)
                max_angle = 80;
            min_power = hit_power - (30  + ((rand() % 10) * 2));
            if(min_power < 10)
                min_power = 10;
            max_power = hit_power + (30 + ((rand() % 10) * 2));
            if(max_power > 100)
                max_power = 100;
        }
    
    
    //player inputs angle
    ai_angle(ai_turret, max_angle, min_angle);
    
    //select power
    ai_power(ai_turret, max_power, min_power);
    
    //shot
    result = shot(ai_turret, player_tank, ai_tank);
    
    //refine range
    {
    turn--;
    
    //final hit
    if(turn == 0){
        min_power = hit_power;
        max_power = hit_power;
        min_angle = hit_angle;
        max_angle = hit_angle;
    }
    
    if(turn != 0){
        rand_result = rand() % 1;
        
        if(result == HIT_SHORT){
                min_angle += (rand() % 1) * 10;
                if(min_angle > hit_angle)
                    min_angle = hit_angle;
                min_power += (rand() % 10) * 2;
                if(min_power > hit_power)
                    min_power = hit_power;
        }
        
        if(result == HIT_LONG){
                max_angle -= (rand() % 1) * 10;
                if(max_angle < hit_angle)
                    max_angle = hit_angle;
                max_power -= (rand() % 10) * 2;
                if(max_power < hit_power)
                    max_power = hit_power;
        }
    }
        
    }
    
    if(result == HIT_TANK || result == HIT_SELF){
        turn = 5;
        hit_bool = 0;
    }
    
    return result;
    
}
//step one (rand angle between min/max)
void ai_angle(struct Turret* ai_turret, int max_angle, int min_angle){
    int new_angle = 0;
    int overflow = 0;
    
    //value to be set
    if(min_angle == max_angle){
        new_angle = min_angle;
    }else{
        new_angle = (rand() % (max_angle - (min_angle + 1)) + min_angle);
        
        if( new_angle % 10 != 0){
            overflow = new_angle % 10;
            new_angle -= overflow;
        }
    }
    
    
    //set angle
    while(ai_turret->angle != new_angle){
        
        //redraw wind bar
        Undraw_Wind_Bar(wind_bar);
        //sample adc
        POT1_Val();
        wind_bar.wind_speed = Wind_Speed_Val();
        //display adc
        Draw_Wind_Bar(wind_bar);
        
        //undraw turret
        Undraw_Turret(ai_turret);
        //Increase angle
        ai_turret->angle += 10;
        if(ai_turret->angle > 80)
            ai_turret->angle = 10;
        //draw turret
        Draw_Turret(ai_turret);
        
        //update LCD
        Write_Buff();
        _delay_ms(50);
            }
    
}
//step two (rand power between min/max)
void ai_power(struct Turret* ai_turret, int max_power, int min_power){
    
    int new_power = 0;
    int overflow = 0;
    
    //value to be set
    if(min_power == max_power){
        new_power = min_power;
    }else{
        new_power = (rand() % (max_power - (min_power + 1)) + min_power);
        
        if( new_power % 2 != 0){
            overflow = new_power % 2;
            new_power -= overflow;
        }
    }
    
    
    //Initialise power bar
    struct Power_Bar power_bar = New_Power_Bar(*ai_turret);
    //Draw power bar
    Draw_Power_Bar(power_bar);
    //update LCD
    Write_Buff();
    
    while(ai_turret->power != new_power){
        
        //redraw wind bar
        Undraw_Wind_Bar(wind_bar);
        //sample adc
        POT1_Val();
        wind_bar.wind_speed = Wind_Speed_Val();
        //display adc
        Draw_Wind_Bar(wind_bar);
        
        //undraw full bar
        Undraw_Power_Bar(power_bar);
        // increase turret power
        ai_turret->power += 2;
        // check if power maxed out
        if(ai_turret->power > 100)
            ai_turret->power = 10;
        power_bar.power = ai_turret->power;
        //Draw updated power bar
        Draw_Power_Bar(power_bar);
        
        //update LCD
        Write_Buff();
        _delay_ms(10);
    }
    
    //undraw power bar
    Undraw_Power_Bar(power_bar);
    //update LCD
    Write_Buff();
    return;

}

//shot
int shot(struct Turret* turret, struct Tank enemy, struct Tank self){
    
    //Variables
    int delay = 20;
    int result = -1;
    
    //initialise bullet
    struct Bullet bullet = New_Bullet(*turret);
    
    // calculate x & y velocity
    Calc_Vel_Init(&bullet);
    //draw bullet
    Draw_Bullet(bullet);
    
    //shot loop
    while(1){
        //update LCD
        Draw_Statics();
        Write_Buff();
        
        //redraw wind bar
        Undraw_Wind_Bar(wind_bar);
        //sample adc
        POT1_Val();
        wind_bar.wind_speed = Wind_Speed_Val();
        //display adc
        Draw_Wind_Bar(wind_bar);
        
        // Update Bullet
        Undraw_Bullet(bullet);
        Calc_Vel_Change(&bullet, wind_bar.wind_speed, delay);
        Calc_Motion(&bullet, delay);
        Draw_Bullet(bullet);
        
        //detect collision
        result =  Detect_Collision(bullet, enemy, self, terrain);
        
        //return collision type
        if(result != IN_FLIGHT){
            Undraw_Bullet(bullet);
            Draw_Statics();
            Write_Buff();
            return result;
        }
        
    }
    
}

//static graphics
void Draw_Statics(){
    Draw_Terrain(terrain);
    Draw_Tank(player_tank);
    Draw_Tank(ai_tank);
    Draw_Turret(&player_turret);
    Draw_Turret(&ai_turret);
}