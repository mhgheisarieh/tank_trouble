
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "newround.h"
#include "logic.h"
#include "maps.h"

void NewRound(Map *map){
    LoadMap (map);
    Definition(map);
}

void Definition(Map* map) {

    map->GameTime = 0;
    map->IsAlive = 1;
    map->frames = 0;

    for (int i=0; i<3; i++){
        map->powerUP[i].enabled= 0;
    }

    srand((unsigned int) time(NULL));

    for (int i = 0; i < map->NumOfTanks; i++) {
        map->tank[i].Key.Right_Key = 0;
        map->tank[i].Key.Up_key = 0;
        map->tank[i].Key.Left_Key = 0;
        map->tank[i].Key.Down_key = 0;
        map->tank[i].CanXPlus = 1;
        map->tank[i].CanYPlus = 1;
        map->tank[i].CanXMinus = 1;
        map->tank[i].CanYMinus = 1;
        map->tank[i].IsAlive = 1;
        map->tank[i].FullDied = 0;
        map->tank[i].NumOFExitBulls = 0;
        map->tank[i].canshoot = 1;
        map->tank[i].IsMined = 0;
        SetXYOfTank(&map->tank[i], map);
        map->tank[i].radius = TankRadius;
        for (int j = 0; j < 9; j++){
            map->tank[i].mine[j].Enabled = 0;
            map->tank[i].mine[j].IsExplosed = 0;
        }
        for (int j = 0; j < NumOfBulls; j++)
            map->tank[i].bullet[j].Exist = 0;
    }

    map->tank[0].BodyColor.r = 250;
    map->tank[0].BodyColor.g = 0;
    map->tank[0].BodyColor.b = 0;
    map->tank[0].BodyColor.a = 210;
    map->tank[0].InnerColor.r = 0;
    map->tank[0].InnerColor.g = 0;
    map->tank[0].InnerColor.b = 0;
    map->tank[0].InnerColor.a = 200;
    map->tank[0].PipeColor.r = 50;
    map->tank[0].PipeColor.g = 50;
    map->tank[0].PipeColor.b = 50;
    map->tank[0].PipeColor.a = 200;
    map->tank[0].ConstBodyColor.r = 250;
    map->tank[0].ConstBodyColor.g = 0;
    map->tank[0].ConstBodyColor.b = 0;
    map->tank[0].ConstBodyColor.a = 210;
    map->tank[0].ConstInnerColor.r = 0;
    map->tank[0].ConstInnerColor.g = 0;
    map->tank[0].ConstInnerColor.b = 0;
    map->tank[0].ConstInnerColor.a = 200;
    map->tank[0].ConstPipeColor.r = 50;
    map->tank[0].ConstPipeColor.g = 50;
    map->tank[0].ConstPipeColor.b = 50;
    map->tank[0].ConstPipeColor.a = 200;
    map->tank[0].Down_key = SDLK_DOWN;
    map->tank[0].Up_key = SDLK_UP;
    map->tank[0].Left_Key = SDLK_LEFT;
    map->tank[0].Right_Key = SDLK_RIGHT;
    map->tank[0].Shoot_Key = SDLK_SLASH;

    map->tank[1].BodyColor.r = 25;
    map->tank[1].BodyColor.g = 100;
    map->tank[1].BodyColor.b = 230;
    map->tank[1].BodyColor.a = 210;
    map->tank[1].InnerColor.r = 0;
    map->tank[1].InnerColor.g = 0;
    map->tank[1].InnerColor.b = 0;
    map->tank[1].InnerColor.a = 200;
    map->tank[1].PipeColor.r = 50;
    map->tank[1].PipeColor.g = 50;
    map->tank[1].PipeColor.b = 50;
    map->tank[1].PipeColor.a = 200;
    map->tank[1].ConstBodyColor.r = 25;
    map->tank[1].ConstBodyColor.g = 100;
    map->tank[1].ConstBodyColor.b = 230;
    map->tank[1].ConstBodyColor.a = 210;
    map->tank[1].ConstInnerColor.r = 0;
    map->tank[1].ConstInnerColor.g = 0;
    map->tank[1].ConstInnerColor.b = 0;
    map->tank[1].ConstInnerColor.a = 200;
    map->tank[1].ConstPipeColor.r = 50;
    map->tank[1].ConstPipeColor.g = 50;
    map->tank[1].ConstPipeColor.b = 50;
    map->tank[1].ConstPipeColor.a = 200;
    map->tank[1].Down_key = SDLK_d;
    map->tank[1].Up_key = SDLK_e;
    map->tank[1].Left_Key = SDLK_s;
    map->tank[1].Right_Key = SDLK_f;
    map->tank[1].Shoot_Key = SDLK_q;
    map->tank[1].Key.Right_Key = 0;
    map->tank[1].Key.Up_key = 0;
    map->tank[1].Key.Left_Key = 0;
    map->tank[1].Key.Down_key = 0;

    if (map->NumOfTanks == 2)
        return;

    map->tank[2].BodyColor.r = 25;
    map->tank[2].BodyColor.g = 230;
    map->tank[2].BodyColor.b = 100;
    map->tank[2].BodyColor.a = 210;
    map->tank[2].InnerColor.r = 0;
    map->tank[2].InnerColor.g = 0;
    map->tank[2].InnerColor.b = 0;
    map->tank[2].InnerColor.a = 200;
    map->tank[2].PipeColor.r = 50;
    map->tank[2].PipeColor.g = 50;
    map->tank[2].PipeColor.b = 50;
    map->tank[2].PipeColor.a = 200;
    map->tank[2].ConstBodyColor.r = 25;
    map->tank[2].ConstBodyColor.g = 230;
    map->tank[2].ConstBodyColor.b = 100;
    map->tank[2].ConstBodyColor.a = 210;
    map->tank[2].ConstInnerColor.r = 0;
    map->tank[2].ConstInnerColor.g = 0;
    map->tank[2].ConstInnerColor.b = 0;
    map->tank[2].ConstInnerColor.a = 200;
    map->tank[2].ConstPipeColor.r = 50;
    map->tank[2].ConstPipeColor.g = 50;
    map->tank[2].ConstPipeColor.b = 50;
    map->tank[2].ConstPipeColor.a = 200;
    map->tank[2].Down_key = SDLK_j;
    map->tank[2].Up_key = SDLK_u;
    map->tank[2].Left_Key = SDLK_h;
    map->tank[2].Right_Key = SDLK_k;
    map->tank[2].Shoot_Key = SDLK_t;
    map->tank[2].Key.Right_Key = 0;
    map->tank[2].Key.Up_key = 0;
    map->tank[2].Key.Left_Key = 0;
    map->tank[2].Key.Down_key = 0;

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