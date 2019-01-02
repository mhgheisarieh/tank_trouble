#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "DefinitionOfTanks.h"
#include "logic.h"

void Definition(Map* map){

    srand(time(NULL));

    SetXYOfTank (&map->tank[0] , map);
    map->tank[0].radius = TankRadius;
    map->tank[0].Color.r = 250;
    map->tank[0].Color.g = 0;
    map->tank[0].Color.b = 0;
    map->tank[0].Color.a = 210;
    map->tank[0].Down_key =SDLK_DOWN;
    map->tank[0].Up_key =SDLK_UP;
    map->tank[0].Left_Key =SDLK_LEFT;
    map->tank[0].Right_Key =SDLK_RIGHT;
    map->tank[0].Shoot_Key = SDLK_m;
    map->tank[0].Key.Right_Key = 0;
    map->tank[0].Key.Up_key = 0;
    map->tank[0].Key.Left_Key = 0;
    map->tank[0].Key.Down_key = 0;
    map->tank[0].CanXPlus = 1;
    map->tank[0].CanYPlus = 1;
    map->tank[0].CanXMinus = 1;
    map->tank[0].CanYMinus = 1;
    map->tank[0].CanDegPlus = 1;
    map->tank[0].CanDegMinus = 1;
    map->tank[0].NumOFExitBulls = 0;
    map->tank[0].canshoot =1;
    for (int i=0; i<NumOfBulls; i++){map->tank[0].bullet[i].Exist = 0;}

    SetXYOfTank (&map->tank[1] , map);
    map->tank[1].radius = TankRadius;
    map->tank[1].Color.r = 25;
    map->tank[1].Color.g = 100;
    map->tank[1].Color.b = 230;
    map->tank[1].Color.a = 210;
    map->tank[1].Down_key =SDLK_d;
    map->tank[1].Up_key =SDLK_e;
    map->tank[1].Left_Key =SDLK_s;
    map->tank[1].Right_Key =SDLK_f;
    map->tank[1].Shoot_Key = SDLK_q;
    map->tank[1].Key.Right_Key = 0;
    map->tank[1].Key.Up_key = 0;
    map->tank[1].Key.Left_Key = 0;
    map->tank[1].Key.Down_key = 0;
    map->tank[1].CanXPlus = 1;
    map->tank[1].CanYPlus = 1;
    map->tank[1].CanXMinus = 1;
    map->tank[1].CanYMinus = 1;
    map->tank[1].CanDegPlus = 1;
    map->tank[1].CanDegMinus = 1;
    map->tank[1].NumOFExitBulls = 0;
    map->tank[1].canshoot =1;
    for (int i=0; i<NumOfBulls; i++){map->tank[1].bullet[i].Exist = 0;}
}

int random_number(int min_num, int max_num){
    int result = 0, low_num = 0, hi_num = 0;
    if (min_num < max_num){
        low_num = min_num;
        hi_num = max_num + 1;
    } else {
        low_num = max_num + 1;
        hi_num = min_num;
    }
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

void SetXYOfTank (Tank* tank , Map* map){
    tank->x = (Sint16) random_number(50, 750);
    tank->y = (Sint16) random_number(50, 750);
    tank->deg =  (double) random_number(1 , 628) / 100;
    if ((!IsTankInWall(map , tank)) && CanYMinus(map , tank) && CanXMinus(map , tank) && CanYPlus(map , tank) && CanXPlus(map , tank))
        return;
    SetXYOfTank(tank , map);
}