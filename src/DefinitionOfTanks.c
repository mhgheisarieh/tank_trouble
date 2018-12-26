#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "DefinitionOfTanks.h"

void Definition(Tank *tank){
    tank[0].x = 500;
    tank[0].y = 500;
    tank[0].deg = 0;
    tank[0].radius = TankRadius;
    tank[0].Color.r = 250;
    tank[0].Color.g = 0;
    tank[0].Color.b = 0;
    tank[0].Color.a = 210;
    tank[0].Down_key =SDLK_DOWN;
    tank[0].Up_key =SDLK_UP;
    tank[0].Left_Key =SDLK_LEFT;
    tank[0].Right_Key =SDLK_RIGHT;
    tank[0].Shoot_Key = SDLK_m;
    tank[0].Key.Right_Key = 0;
    tank[0].Key.Up_key = 0;
    tank[0].Key.Left_Key = 0;
    tank[0].Key.Down_key = 0;
    tank[0].CanXPlus = 1;
    tank[0].CanYPlus = 1;
    tank[0].CanXMinus = 1;
    tank[0].CanYMinus = 1;
    tank[0].NumOFExitBulls = 0;
    tank[0].canshoot =1;
    for (int i=0; i<NumOfBulls; i++){tank[0].bullet[i].Exist = 0;}

    tank[1].x = 170;
    tank[1].y = 170;
    tank[1].deg = 1.57;
    tank[1].radius = TankRadius;
    tank[1].Color.r = 25;
    tank[1].Color.g = 100;
    tank[1].Color.b = 230;
    tank[1].Color.a = 210;
    tank[1].Down_key =SDLK_d;
    tank[1].Up_key =SDLK_e;
    tank[1].Left_Key =SDLK_s;
    tank[1].Right_Key =SDLK_f;
    tank[1].Shoot_Key = SDLK_q;
    tank[1].Key.Right_Key = 0;
    tank[1].Key.Up_key = 0;
    tank[1].Key.Left_Key = 0;
    tank[1].Key.Down_key = 0;
    tank[1].CanXPlus = 1;
    tank[1].CanYPlus = 1;
    tank[1].CanXMinus = 1;
    tank[1].CanYMinus = 1;
    tank[1].NumOFExitBulls = 0;
    tank[1].canshoot =1;
    for (int i=0; i<NumOfBulls; i++){tank[1].bullet[i].Exist = 0;}
}