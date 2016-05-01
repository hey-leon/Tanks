//
//  Physics.c
//  
//
//  Created by Leon Michael Mitchel Pearce on 1/10/2014.
//
//

#include "Physics.h"

//Calculate directional velocity
void Calc_Vel_Init(struct Bullet* bullet){
    
    //Variables
    float KE; // Kinetic energy of propulsion
    float M;  // Mass of bullet
    float V;  // Velocity of bullet (m/s) on vector
    
    /* mass equation
     *
     *           weight
     *     M = ----------
     *           gravity
     *
     */
    
    M = bullet->weight / GRAVITY;
    
    /* Kinetic energy equation
     *
     *        max kinetic
     *  KE = -------------  *  Power
     *            100
     *
     */
    
    KE = (MAX_KINETIC / 100) * bullet->power;
    
    /* directional velocity equation
     *
     *
     * V = sqroot(KE * M / .5)
     *
     *
     */
    
    V =  sqrt(KE * M /.5);
    
    /* X velocity equation
     *
     *
     * x velocity = V * Cos( angle (radians) )
     *
     *
     */
    bullet->x_vel = V * cos(bullet->angle * M_PI / 180);
    
    /* Y velocity equation
     *
     *
     * y velocity = V * Sin( angle (radians) )
     *
     *
     */
    bullet->y_vel = V * sin(bullet->angle * M_PI / 180);
    
}

void Calc_Kill_Ratio(int power, int angle, int weight, float* x_vel, float* y_vel){
    
    //Variables
    float KE; // Kinetic energy of propulsion
    float M;  // Mass of bullet
    float V;  // Velocity of bullet (m/s) on vector
    
    /* mass equation
     *
     *           weight
     *     M = ----------
     *           gravity
     *
     */
    
    M = weight / GRAVITY;
    
    /* Kinetic energy equation
     *
     *        max kinetic
     *  KE = -------------  *  Power
     *            100
     *
     */
    
    KE = (MAX_KINETIC / 100) * power;
    
    /* directional velocity equation
     *
     *
     * V = sqroot(KE * M / .5)
     *
     *
     */
    
    V =  sqrt(KE * M /.5);
    
    /* X velocity equation
     *
     *
     * x velocity = V * Cos( angle (radians) )
     *
     *
     */
    *x_vel = V * cos(angle * M_PI / 180);
    
    /* Y velocity equation
     *
     *
     * y velocity = V * Sin( angle (radians) )
     *
     *
     */
    *y_vel = V * sin(angle * M_PI / 180);
    
}

int Validate_Kill_Ratio(float x_vel, float y_vel, int wind_speed, int distance){
    float T = 0;
    int test_d;
    
    T = (float)(2 * y_vel)/ GRAVITY;
    
    test_d = (x_vel * T) + ((-(wind_speed * .25) / 2) * (T * T));
    
    if(test_d < distance - 1 && test_d > distance - 6)
        return 1;
        
    
    return 0;
}

void Calc_Vel_Change(struct Bullet* bullet, int wind_speed, int delay){
    int T = 1000 / delay; // time of deceleration (s)
    
    /* Effect of gravity
     *
     * y_vel -= gravity / T
     *
     */
    
    bullet->y_vel -= GRAVITY / T;
    
    /* Friction Coefficient
     *
     *
     * F = weight * air/material coefficient (.0125)
     *
     *
     */
    const float F = bullet->weight * .0125; // friction coefficient
    
    /* Effect of wind
     *
     * y_vel -= (wind * F) / T
     *
     */
    
    bullet->x_vel += (float)((bullet->direction * wind_speed) * F) / T;
}

void Calc_Motion(struct Bullet* bullet, int delay){
    
    //Variables
    int T = 1000 / delay;
    
    /* Calculate distance of x shift
     *
     *                           x_vel
     * distance = direction * (---------)
     *                           T (s)
     *
     */
    
    bullet->x += bullet->direction * (bullet->x_vel / T);
    
    /* Calculate distance of y shift
     *
     *              y_vel
     * distance = ---------
     *              t (s)
     *
     */
    
    bullet->y += (bullet->y_vel / T);
    
}

int Detect_Collision(struct Bullet bullet, struct Tank enemy, struct Tank self, struct Terrain terrain){
    
    //ground collision
    if ((bullet.y - bullet.height) + 1  < terrain.height){
        // direction - right
        if (bullet.direction == 1){
            if (bullet.x > (enemy.x + enemy.width)){
                //hit long
                Explosion(bullet.x + bullet.direction, bullet.y, bullet.direction);
                return HIT_LONG;
            }
            if ((bullet.x + bullet.width) < enemy.x){
                //hit short
                Explosion(bullet.x + bullet.direction, bullet.y, bullet.direction);
                return HIT_SHORT;
            }
        }
        // direction - left
        if (bullet.direction == -1){
            if (bullet.x > (enemy.x + enemy.width)){
                //hit short
                Explosion(bullet.x + bullet.direction, bullet.y, bullet.direction);
                return HIT_SHORT;
            }
            if ((bullet.x + bullet.width) < enemy.x){
                //hit long
                Explosion(bullet.x + bullet.direction, bullet.y, bullet.direction);
                return HIT_LONG;
            }
        }
    }
    
    //suicide collision
    if(bullet.x > self.x && bullet.x + bullet.width < self.x + self.width  && bullet.y - bullet.height + 2 < self.y){
       //suicide
        Explosion(bullet.x + bullet.direction, bullet.y, bullet.direction);
        return HIT_SELF;
    }
    
    //enemy collision
    if(bullet.x + bullet.width > enemy.x && bullet.x < enemy.x + enemy.width  && bullet.y - bullet.height + 2 < enemy.y){
        //suicide
        Explosion(bullet.x + bullet.direction, bullet.y, bullet.direction);
        return HIT_TANK;
    }
    
    //out of bounds
    // direction - right
    if (bullet.direction == 1){
        if (bullet.x > (terrain.width + 20)){
            //hit long
            return HIT_LONG;
        }
        if ((bullet.x + bullet.width) < -20){
            //hit short
            return HIT_SHORT;
        }
    }
    // direction - left
    if (bullet.direction == -1){
        if (bullet.x > (terrain.width + 20)){
            //hit short
            return HIT_SHORT;
        }
        if ((bullet.x + bullet.width) < -20){
            //hit long
            return HIT_LONG;
        }
    }
    
    return IN_FLIGHT;
}

