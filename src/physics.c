#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "physics.h"

void moveTank(Tank* tank) {
    if (!(tank->Key.Up_key && tank->Key.Down_key)){
        if (tank->Key.Up_key){
            tank->y += Step*(sinf(tank->deg));
            tank->x += Step*(cosf(tank->deg));
        }
        if (tank->Key.Down_key){
            tank->y -= Step*(sinf(tank->deg));
            tank->x -= Step*(cosf(tank->deg));
        }
    }
}

void turnTank(Tank* tank){
    if (tank->Key.Right_Key)
        tank->deg += DegStep;
    if (tank->Key.Left_Key)
        tank->deg -= DegStep;
}

void fire(Tank* tank){
    if (tank->NumOFExitBulls == NumOfBulls) return;
    int i;
    for (i=0; i<NumOfBulls; i++)
        if (tank->bullet[i].Exist==0){
            break;
        }
    tank->bullet[i].Exist =1;
    tank->bullet[i].deg = tank->deg;
    tank->bullet[i].x = tank->x + 27*(cosf(tank->deg));
    tank->bullet[i].y = tank->y + 27*(sinf(tank->deg));
    tank->bullet[i].TimeAppear = SDL_GetTicks();
    tank->NumOFExitBulls ++;
}

void move_bullet(Bullet* bullet){
    bullet->y += BullStep*(sinf(bullet->deg));
    bullet->x += BullStep*(cosf(bullet->deg));
}