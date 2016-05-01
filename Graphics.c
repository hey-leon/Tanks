//
//  Graphics.c
//
//
//  Created by Leon Michael Mitchel Pearce on 27/09/2014.
//
//

#include "Graphics.h"


//------------------Global Variables---------------------//

//Screen buffer
unsigned char screen_buff[LCD_WIDTH][LCD_ROWS];


//-------------------Functions----------------------------//

//General Functions
void Write_Buff(void) {

    
    //Variables
    char write_buff = 0;
    char i = 0;
    char j = 0;
    
    //Put cursor at start of screen **** possibly redundent
    LCD_Pos(0,0);
    
    //For each row
    for(i = 0; i < LCD_ROWS; i++){
        //For each column
        for(j = 0; j < LCD_WIDTH; j++){
            //Write to column j, row i.
            LCD_Write(LCD_DATA, screen_buff[j][i]);
        }
    }
    
    
}
void Clear_Buff(void) {
    
    
    //Variables
    int x = 0;
    int y = 0;
    
    //Loop for each column
    for(x = 0; x < LCD_WIDTH; x++){
        //Loop for each row
        for(y = 0; y < LCD_ROWS; y++){
            screen_buff[x][y] = 0;
        }
    }
    
    
}
void Draw_Pixel(unsigned char x, unsigned char y){

    
    //Variables
    unsigned char shift = 0;
    unsigned char row = 0;
    
    
    //Find how far to shift into row
    shift = y % WRITE_HEIGHT;
    
    //Remove shift from y
    y -= shift;
    
    //Find row
    while(y != 0){
        y -= WRITE_HEIGHT;
        row++;
    }
    //check row and x
    if(row >= ROW0 && row <= ROW5 && x >= 0 && x < LCD_WIDTH){
        //Draw pixel to buffer
        screen_buff[x][row] |= (1 << shift);
    }
    
    
}
void Undraw_Pixel(unsigned char x, unsigned char y){

    //Variables
    unsigned char shift = 0;
    unsigned char row = 0;
    
    
    //Find how far to shift into row
    shift = y % WRITE_HEIGHT;
    
    //Remove shift from y
    y -= shift;
    
    //Find row
    while(y != 0){
        y -= WRITE_HEIGHT;
        row++;
    }
    //check row and x
    if(row >= ROW0 && row <= ROW5 && x >= 0 && x < LCD_WIDTH){
        //Undraw pixel to buffer
        screen_buff[x][row] &= ~(1 << shift);
    }

    
    
    
}

//draw char/undraw char - returns width of draw
int Draw_Char(unsigned char character, int x, int y){
    
    //variables
    int j = 0; //char column
    int k = 0; //char row
    int l = 0; //cursor
    
    //write char
    for(j = 0; j < 5; j++){
        for(k = 0; k < 8; k++){
            //checks each bit of each char segment and draws if == 1.
            if((ASCII[character - 0x20][j] >> k) & (1 << 0) == 1){
                Draw_Pixel((x + l), y + k);
            }
        }
        l++;
    }
    
    return l;
}
int Undraw_Char(unsigned char character, int x, int y){
    
    //variables
    int j = 0; //char column
    int k = 0; //char row
    int l = 0; //cursor
    
    //write char
    for(j = 0; j < 5; j++){
        for(k = 0; k < 8; k++){
            //checks each bit of each char segment and draws if == 1.
            if((ASCII[character - 0x20][j] >> k) & (1 << 0) == 1){
                Undraw_Pixel((x + l), y + k);
            }
        }
        l++;
    }
    
    return l;
}
//draw string/undraw string - returns width of draw
int Draw_String(char* string, int x, int y){
    //variables
    int i = 0;
    int j = 0; //char column
    int k = 0; //char row
    int l = 0; //cursor
    

    
    //draw string
    while(string[i] != '\0'){
        //empty space
        l++;
        //write char
        for(j = 0; j < 5; j++){
            for(k = 0; k < 8; k++){
                //checks each bit of each char segment and draws if == 1.
                if((ASCII[string[i] - 0x20][j] >> k) & (1 << 0) == 1){
                    Draw_Pixel((x + l), y + k);
                }
            }
            l++;
        }
        i++;
    }
    
    return l;
}
int Undraw_String(char* string, int x, int y){
    //variables
    int i = 0;
    int j = 0; //char column
    int k = 0; //char row
    int l = 0; //cursor
    
    
    
    //draw string
    while(string[i] != '\0'){
        //empty space
        l++;
        //write char
        for(j = 0; j < 5; j++){
            for(k = 0; k < 8; k++){
                //checks each bit of each char segment and draws if == 1.
                if((ASCII[string[i] - 0x20][j] >> k) & (1 << 0) == 1){
                    Undraw_Pixel((x + l), y + k);
                }
            }
            l++;
        }
        i++;
    }
    
    return l;
}
//draw int/undraw int - returns width of draw
int Draw_int(int i, unsigned int places, int x, int y) {
    //variables
    int l = 0;
    
    //make i positive
    if (i < 0) {
        i *= -1;
    }
    
    unsigned int ii, iii, iiii;
    int divisor;
    
    for (ii = places; ii>0; ii--) {
        divisor = 1;
        for (iiii = ii-1; iiii>0; iiii--) {
            divisor *= 10;
        }
        iii = i / divisor;
        i -= iii*divisor;
        switch(iii) {
            case 0:
                l += Draw_Char('0', x + l, y);
                break;
            case 1:
                l += Draw_Char('1', x + l, y);
                break;
            case 2:
                l += Draw_Char('2', x + l, y);
                break;
            case 3:
                l += Draw_Char('3', x + l, y);
                break;
            case 4:
                l += Draw_Char('4', x + l, y);
                break;
            case 5:
                l += Draw_Char('5', x + l, y);
                break;
            case 6:
                l += Draw_Char('6', x + l, y);
                break;
            case 7:
                l += Draw_Char('7', x + l, y);
                break;
            case 8:
                l += Draw_Char('8', x + l, y);
                break;
            case 9:
                l += Draw_Char('9', x + l, y);
                break;
        }
        l += 1;
    }
    
    return l;
}
int Undraw_int(int i, unsigned int places, int x, int y) {
    //variables
    int l = 0;
    
    //make i positive
    if (i < 0) {
        i *= -1;
    }
    
    unsigned int ii, iii, iiii;
    int divisor;
    
    for (ii = places; ii>0; ii--) {
        divisor = 1;
        for (iiii = ii-1; iiii>0; iiii--) {
            divisor *= 10;
        }
        iii = i / divisor;
        i -= iii*divisor;
        switch(iii) {
            case 0:
                l += Undraw_Char('0', x + l, y);
                break;
            case 1:
                l += Undraw_Char('1', x + l, y);
                break;
            case 2:
                l += Undraw_Char('2', x + l, y);
                break;
            case 3:
                l += Undraw_Char('3', x + l, y);
                break;
            case 4:
                l += Undraw_Char('4', x + l, y);
                break;
            case 5:
                l += Undraw_Char('5', x + l, y);
                break;
            case 6:
                l += Undraw_Char('6', x + l, y);
                break;
            case 7:
                l += Undraw_Char('7', x + l, y);
                break;
            case 8:
                l += Undraw_Char('8', x + l, y);
                break;
            case 9:
                l += Undraw_Char('9', x + l, y);
                break;
        }
        l += 1;
    }
    return l;
}

//Draw Graphics
void Draw_Bullet(struct Bullet bullet){
    
    //Variables
    char i = 0;
    char j = 0;
    
    //Draw pixels
    for(i = 0; i < bullet.width; i++){
        for(j = 0; j < bullet.height; j++){
            Draw_Pixel(bullet.x + i, (LCD_HEIGHT - bullet.y) + j);
        }
    }
   
    
}
void Draw_Tank(struct Tank tank){

    //Variables
    char i = 0;
    char j = 0;
    
    //Draw hatch
    Draw_Pixel(tank.x + 2, LCD_HEIGHT - tank.y);
    
    //Draw body
    for(j = 1; j < tank.height; j++){
        for(i = 0; i < tank.width; i++){
            Draw_Pixel(tank.x + i, (LCD_HEIGHT - tank.y) + j);
        }
    }
    
    
}
void Draw_Turret(struct Turret* turret){
    //Variables
    float gradient;
    char i = 0;
    
    switch (turret->angle) {
        case 10:
            gradient = -.20;
            break;
        case 20:
            gradient = -.38;
            break;
        case 30:
            gradient = -.54;
            break;
        case 40:
            gradient = -.68;
            break;
        case 50:
            gradient = -.79;
            break;
        case 60:
            gradient = -.68;
            break;
        case 70:
            gradient = -.54;
            break;
        case 80:
            gradient = -.38;
            break;
    }
    
    //slight angle
    if(turret->angle < 45){
        
        for(i = 0; i < turret->length; i++){
            Draw_Pixel(turret->x + (turret->direction * i),
                       LCD_HEIGHT - turret->y + ceil(i * gradient));
            //update x2/y2
            if(i == turret->length - 1){
                turret->x2 = turret->x + (turret->direction * i + 1);
                turret->y2 = turret->y - ceil(i * gradient);
            }
        }
    }
    
    //steep angle
    if(turret->angle > 45){
        
        for(i = 0; i < turret->length; i++){
            Draw_Pixel(turret->x + trunc(turret->direction * i * -gradient),
                       LCD_HEIGHT - turret->y - i);
            //update x2/y2
            if(i == turret->length - 1){
                turret->x2 = turret->x + trunc(turret->direction * i * -gradient);
                turret->y2 = turret->y + i + 3;
            }
        }
    }
    
    
}
void Draw_Terrain(struct Terrain terrain){
    

    //Variables
    char draw_bool = 1; //1 == True, 0 == False.
    char i = 0;
    char j = 0;
    
    //Draw upper boundary
    for(j = 0; j < terrain.width; j++)
        Draw_Pixel(j, LCD_HEIGHT - terrain.height);
    
    //Fill ground with checkers
    for(i = 1; i < terrain.height; i++){
        for(j = 0; j < terrain.width; j++){
            //Draw bool check for each pixel
            if(draw_bool == 1){
                Draw_Pixel(j, LCD_HEIGHT - (terrain.height - i));
                draw_bool = 0;
            }else{
                draw_bool = 1;
            }
            
        }
        //Alternate draw bool on new line
        if(draw_bool == 1){
            draw_bool = 0;
        }else{
            draw_bool = 1;
        }
    }
    
    
}
void Draw_Power_Bar(struct Power_Bar power_bar){
    
    //variables
    int i = 0; //current char
    int j = 0; //vertical segment
    int k = 0; //bit of vertical segment
    int l = 0; //cursor
    
    //draw label
    while(power_bar.label[i] != '\0'){
        //empty space
        l++;
        //write char
        for(j = 0; j < 5; j++){
            for(k = 0; k < 8; k++){
                //checks each bit of each char segment and draws if == 1.
                if((ASCII[power_bar.label[i] - 0x20][j] >> k) & (1 << 0) == 1){
                    Draw_Pixel((power_bar.x + l), power_bar.y + k);
                }
            }
            l++;
        }
        i++;
    }
    
    l += 3;
    
    //draw bar
    for(j = 0; j <= 50; j++){
        if(j == 0 || j == 50 || power_bar.power / 2 >= j){
            //fill
            for(k = 0; k < 8; k++){
                if((BAR_FILL >> k) & (1 << 0) == 1){
                    Draw_Pixel((power_bar.x + l), power_bar.y + k);
                }
            }
        }else{
            //edges
            for(k = 0; k < 8; k++){
                if((BAR_EDGE >> k) & (1 << 0) == 1){
                    Draw_Pixel((power_bar.x + l), power_bar.y + k);
                }
            }
        }
        l++;
    }
    
}
void Draw_Wind_Bar(struct Wind_Bar wind_bar){
    
    //variables
    int l = 0; //cursor
    
    //draw label
    l += Draw_String(wind_bar.label, wind_bar.x, wind_bar.y);
    
    l += 22;
    
    char tens;
    char ones;
    
    //break wind_speed into vector and draw
    if (wind_bar.wind_speed < 0){
        l += Draw_Char( 0x3c, wind_bar.x + l, wind_bar.y);
        l += 2;
        l += Draw_int(-wind_bar.wind_speed, 2, wind_bar.x + l, wind_bar.y);
    } else {
        l += Draw_Char( 0x3e, wind_bar.x + l, wind_bar.y);
        l += 2;
        l += Draw_int(wind_bar.wind_speed, 2, wind_bar.x + l, wind_bar.y);
    }
    
    
    //draw m/s
    char* mpers = "m/s";
    
    Draw_String(mpers, wind_bar.x + l, wind_bar.y);
    
    
    

}

//Undraw Graphics
void Undraw_Bullet(struct Bullet bullet){
    
    //Variables
    char i = 0;
    char j = 0;
    
    //Draw pixels
    for(i = 0; i < bullet.width; i++){
        for(j = 0; j < bullet.height; j++){
            Undraw_Pixel(bullet.x + i, (LCD_HEIGHT - bullet.y) + j);
        }
    }
    
    
}
void Undraw_Turret(struct Turret* turret) {
    //Variables
    float gradient;
    char i = 0;
    
    switch (turret->angle) {
        case 10:
            gradient = -.20;
            break;
        case 20:
            gradient = -.38;
            break;
        case 30:
            gradient = -.54;
            break;
        case 40:
            gradient = -.68;
            break;
        case 50:
            gradient = -.79;
            break;
        case 60:
            gradient = -.68;
            break;
        case 70:
            gradient = -.54;
            break;
        case 80:
            gradient = -.38;
            break;
    }
    
    //slight angle
    if(turret->angle < 45){
        for(i = 0; i < turret->length; i++){
            Undraw_Pixel(turret->x + (turret->direction * i),
                       LCD_HEIGHT - turret->y + ceil(i * gradient));
            //update x2/y2
            if(i == turret->length - 1){
                turret->x2 = turret->x + (turret->direction * i + 1);
                turret->y2 = turret->y - ceil(i * gradient);
            }
        }
    }
    
    //steep angle
    if(turret->angle > 45){
        for(i = 0; i < turret->length; i++){
            Undraw_Pixel(turret->x + trunc(turret->direction * i * -gradient),
                       LCD_HEIGHT - turret->y - i);
            //update x2/y2
            if(i == turret->length - 1){
                turret->x2 = turret->x + trunc(turret->direction * i * -gradient);
                turret->y2 = turret->y + i + 3;
            }
        }
    }
    
    
    
}
void Undraw_Power_Bar(struct Power_Bar power_bar){
    
    //variables
    int i = 0; //current char
    int j = 0; //vertical segment
    int k = 0; //bit of vertical segment
    int l = 0; //cursor
    
    //draw label
    while(power_bar.label[i] != '\0'){
        //empty space
        l++;
        //write char
        for(j = 0; j < 5; j++){
            for(k = 0; k < 8; k++){
                //checks each bit of each char segment and draws if == 1.
                if((ASCII[power_bar.label[i] - 0x20][j] >> k) & (1 << 0) == 1){
                    Undraw_Pixel((power_bar.x + l), power_bar.y + k);
                }
            }
            l++;
        }
        i++;
    }
    
    l += 3;
    
    //draw bar
    for(j = 0; j <= 50; j++){
        if(j == 0 || j == 50 || power_bar.power >= j){
            //fill
            for(k = 0; k < 8; k++){
                if((BAR_FILL >> k) & (1 << 0) == 1){
                    Undraw_Pixel((power_bar.x + l), power_bar.y + k);
                }
            }
        }else{
            //edges
            for(k = 0; k < 8; k++){
                if((BAR_EDGE >> k) & (1 << 0) == 1){
                    Undraw_Pixel((power_bar.x + l), power_bar.y + k);
                }
            }
        }
        l++;
    }
    
}
void Undraw_Wind_Bar(struct Wind_Bar wind_bar){
    
    //variables
    int l = 0; //cursor
    
    //draw label
    l += Undraw_String(wind_bar.label, wind_bar.x, wind_bar.y);

    l += 22;
    
    char speed;
    
    //break wind_speed into vector and draw
    if (wind_bar.wind_speed < 0){
        l += Undraw_Char( 0x3c, wind_bar.x + l, wind_bar.y);
        l += 2;
        l += Undraw_int(-wind_bar.wind_speed, 2, wind_bar.x + l, wind_bar.y);
    } else {
        l += Undraw_Char( 0x3e, wind_bar.x + l, wind_bar.y);
        l += 2;
        l += Undraw_int(wind_bar.wind_speed, 2, wind_bar.x + l, wind_bar.y);
    }
    
    
    //draw m/s
    char* mpers = "m/s";
    
    Undraw_String(mpers, wind_bar.x + l, wind_bar.y);
    
    

}

//effects
void Explosion(int x, int y, int direction){
    //variables
    int i = 0;
    
    //draw explosion
    for(i = 0; i < 4; i++){
        //draw
        //shrapnel 1
        Draw_Pixel( x + (-direction*(1.5*i)), (LCD_HEIGHT) - (y + (2*i)));
        //shrapnel 2
        Draw_Pixel( x + (-direction*i), (LCD_HEIGHT) - (y + (2*i)));
        //shrapnel 3
        Draw_Pixel( x, (LCD_HEIGHT) - (y + (2*i)));
        
        Draw_Statics();
        Write_Buff();
        _delay_ms(100);
        //undraw
        //shrapnel 1
        Undraw_Pixel( x + (-direction*(1.5*i)), (LCD_HEIGHT) - (y + (2*i)));
        //shrapnel 2
        Undraw_Pixel( x + (-direction*i), (LCD_HEIGHT) - (y + (2*i)));
        //shrapnel 3
        Undraw_Pixel( x, (LCD_HEIGHT) - (y + (2*i)));
    }
    
}
