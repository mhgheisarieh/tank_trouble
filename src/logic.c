#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "struct.h"
#include "logic.h"

void IsWall (Map* map){
    for (int i=0 ; i<NumOfTank; i++){
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
            if (map->wall[i].Ry2 + TankRadius - 7 > tank->y
            && map->wall[i].Ry1 - TankRadius + 7 < tank->y
            && map->wall[i].Rx1 - tank->x <= TankRadius + 4
            && map->wall[i].Rx1 - tank->x >= 0 )
                can = 0;
        }
        if (map->wall[i].Ry1 == map->wall[i].Ry2){
            if (map->wall[i].Rx1 - tank->x <= TankRadius + 2
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
            if (map->wall[i].Ry2 + TankRadius - 7 > tank->y
                && map->wall[i].Ry1 - TankRadius + 7 < tank->y)
            {
                if (tank->x - map->wall[i].Rx1 <= TankRadius + 4
                    && map->wall[i].Rx1 - tank->x <= 0)
                    can =0;
            }
        }
        if (map->wall[i].Ry1 == map->wall[i].Ry2){
            if (tank->x - map->wall[i].Rx2<= TankRadius + 2
                && tank->x - map->wall[i].Rx2 > 0
                && tank->y - map->wall[i].Ry1 <= TankRadius
                && tank->y - map->wall[i].Ry1 >= -TankRadius )
                can = 0;
        }
    }
    return can;
}

bool CanYPlus (Map* map , Tank* tank){
    bool can =1;
    for (int i=0 ; i<map->NumOfWalls; i++){
        if (map->wall[i].Ry1 == map->wall[i].Ry2){
            if (map->wall[i].Rx2 + TankRadius - 7 > tank->x
                && map->wall[i].Rx1 - TankRadius + 7 < tank->x
                && map->wall[i].Ry1 - tank->y <= TankRadius + 4
                && map->wall[i].Ry1 - tank->y >= 0)
                can = 0;
        }
        if (map->wall[i].Rx1 == map->wall[i].Rx2){
            if (map->wall[i].Ry1 - tank->y <= TankRadius + 2
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
            if (map->wall[i].Rx2 + TankRadius - 7 > tank->x
                && map->wall[i].Rx1 - TankRadius + 7 < tank->x)
            {
                if (tank->y - map->wall[i].Ry1 <= TankRadius + 4
                    && map->wall[i].Ry1 - tank->y <= 0)
                    can =0;
            }
        }
        if (map->wall[i].Rx1 == map->wall[i].Rx2){
            if (tank->y - map->wall[i].Ry2<= TankRadius + 2
                && tank->y - map->wall[i].Ry2 > 0
                && tank->x - map->wall[i].Rx1 <= TankRadius
                && tank->x - map->wall[i].Rx1 >= -TankRadius )
                can = 0;
        }
    }
    return can;
}