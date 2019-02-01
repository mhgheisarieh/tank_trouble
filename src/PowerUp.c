

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "struct.h"
#include "PowerUp.h"
#include "newround.h"

void MakePowerUp (Map* map){
    int i=0;
    for (; i<3; i++){
        if (map->powerUP[i].enabled == 0){
            map->powerUP[i].enabled = 1;
            break;
        }
        if (i==2) return;
    }
    do{
        map->powerUP[i].x = (Sint16) random_number(50, 750);
        map->powerUP[i].y = (Sint16) random_number(50, 750);
    }while (IsPowerUpInWall (map ,map->powerUP));
}

bool IsPowerUpInWall (Map* map , PowerUP* powerUP){
    bool IsInWall = 0;
    for (int i=0 ; i <map->NumOfWalls ; i++){
        if (    ( powerUP->x < ((int) map->wall[i].Rx2  + 40))
                &&  (powerUP->x > ((int) map->wall[i].Rx1  - 40))
                &&  (powerUP->y < ((int) map->wall[i].Ry2  + 40))
                &&  (powerUP->y > ((int) map->wall[i].Ry1 - 40))   ){
            IsInWall = 1;
            break;
        }
    }
    return IsInWall;
}