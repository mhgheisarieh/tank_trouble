#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "struct.h"
#include "logic.h"
#include "physics.h"

void Logics (Map* map){
    for (int i=0 ; i<map->NumOfTanks; i++){
        map->tank[i].CanXPlus = CanXPlus (map , &map->tank[i]);
        map->tank[i].CanXMinus = CanXMinus (map , &map->tank[i]);
        map->tank[i].CanYPlus = CanYPlus (map , &map->tank[i]);
        map->tank[i].CanYMinus = CanYMinus (map , &map->tank[i]);
    }
}

bool CanXPlus (Map* map , Tank* tank){
    bool can =1;
    for (int i=0 ; i<map->NumOfWalls; i++){
        if (map->wall[i].Rx1 == map->wall[i].Rx2){
            if (map->wall[i].Ry2 + TankRadius - Step > tank->y
            && map->wall[i].Ry1 - TankRadius + Step < tank->y
            && map->wall[i].Rx1 - tank->x <= TankRadius + Step
            && map->wall[i].Rx1 - tank->x >= 0 )
                can = 0;
        }
        if (map->wall[i].Ry1 == map->wall[i].Ry2){
            if (map->wall[i].Rx1 - tank->x <= TankRadius + Step
            && map->wall[i].Rx1 - tank->x > 0
            && tank->y - map->wall[i].Ry1 <= TankRadius
            && tank->y - map->wall[i].Ry1 >= -TankRadius )
                can = 0;
        }
    }
    return can;
}

bool CanXMinus (Map* map , Tank* tank){
    bool can =1;
    for (int i=0 ; i<map->NumOfWalls; i++){
        if (map->wall[i].Rx1 == map->wall[i].Rx2){
            if (map->wall[i].Ry2 + TankRadius - Step > tank->y
                && map->wall[i].Ry1 - TankRadius + Step < tank->y
                && tank->x - map->wall[i].Rx1 <= TankRadius + Step
                && map->wall[i].Rx1 - tank->x <= 0)
                    can =0;
        }
        if (map->wall[i].Ry1 == map->wall[i].Ry2){
            if (tank->x - map->wall[i].Rx2<= TankRadius + Step
                && tank->x - map->wall[i].Rx2 > 0
                && tank->y - map->wall[i].Ry1 <= TankRadius
                && tank->y - map->wall[i].Ry1 >= -TankRadius)
                    can = 0;
        }
    }
    return can;
}

bool CanYPlus (Map* map , Tank* tank){
    bool can =1;
    for (int i=0 ; i<map->NumOfWalls; i++){
        if (map->wall[i].Ry1 == map->wall[i].Ry2){
            if (map->wall[i].Rx2 + TankRadius - Step > tank->x
                && map->wall[i].Rx1 - TankRadius + Step < tank->x
                && map->wall[i].Ry1 - tank->y <= TankRadius + Step
                && map->wall[i].Ry1 - tank->y >= 0)
                can = 0;
        }
        if (map->wall[i].Rx1 == map->wall[i].Rx2){
            if (map->wall[i].Ry1 - tank->y <= TankRadius + Step
                && map->wall[i].Ry1 - tank->y > 0
                && tank->x - map->wall[i].Rx1 <= TankRadius
                && tank->x - map->wall[i].Rx1 >= -TankRadius )
                can = 0;
        }
    }
    return can;
}


bool CanYMinus (Map* map , Tank* tank){
    bool can =1;
    for (int i=0 ; i<map->NumOfWalls; i++){
        if (map->wall[i].Ry1 == map->wall[i].Ry2){
            if (map->wall[i].Rx2 + TankRadius - Step > tank->x
                && map->wall[i].Rx1 - TankRadius + Step < tank->x
                && tank->y - map->wall[i].Ry1 <= TankRadius + Step
                && map->wall[i].Ry1 - tank->y <= 0)
                    can =0;
        }
        if (map->wall[i].Rx1 == map->wall[i].Rx2){
            if (tank->y - map->wall[i].Ry2<= TankRadius + Step
                && tank->y - map->wall[i].Ry2 > 0
                && tank->x - map->wall[i].Rx1 <= TankRadius
                && tank->x - map->wall[i].Rx1 >= -TankRadius )
                can = 0;
        }
    }
    return can;
}

bool IsTankInWall (Map* map , Tank* tank){
    bool IsInWall = 0;
    for (int i=0 ; i <map->NumOfWalls ; i++){
        if (    ((int) tank->x < ((int) map->wall[i].Rx2 + TankRadius + 15))
            &&  ((int) tank->x > ((int) map->wall[i].Rx1 - TankRadius - 15))
            &&  ((int) tank->y < ((int) map->wall[i].Ry2 + TankRadius + 15))
            &&  ((int) tank->y > ((int) map->wall[i].Ry1 - TankRadius - 15))   ){
            IsInWall = 1;
            break;
        }
    }
    return IsInWall;
}

bool IsAliveBullet (int GameTime , Bullet* bullet){
    if (GameTime-(bullet->TimeAppear)>TimeOfBull) {
        bullet->Exist = 0;
        return 0;
    }
    return 1;
}
