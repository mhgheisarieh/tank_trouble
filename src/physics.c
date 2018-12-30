#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "physics.h"

int IsPlus(double i){
    if (i>=0) return 1;
    return 0;
}
void moveTank(Tank* tank) {
    if (tank->Key.Up_key && tank->Key.Down_key) return;
    if (tank->Key.Up_key){
        if (IsPlus(sin(tank->deg))){
            if (tank->CanYPlus)
                tank->y = (Sint16) (tank->y + Step *(sinf((float) tank->deg)));
        } else {
            if (tank->CanYMinus)
                tank->y = (Sint16) (tank->y + Step *(sinf((float) tank->deg)));
        }
        if (IsPlus(cos(tank->deg))){
            if (tank->CanXPlus)
                tank->x = (Sint16) (tank->x + Step *(cosf((float) tank->deg)));
        } else {
            if (tank->CanXMinus)
                tank->x = (Sint16) (tank->x + Step *(cosf((float) tank->deg)));
        }
    }
    if (tank->Key.Down_key){
        if (IsPlus(sin(tank->deg))){
            if (tank->CanYMinus)
                tank->y -= Step*(sinf(tank->deg));
        } else {
            if (tank->CanYPlus)
                tank->y -= Step*(sinf(tank->deg));
        }
        if (IsPlus(cos(tank->deg))){
            if (tank->CanXMinus)
                tank->x -= Step*(cosf(tank->deg));
        } else {
            if (tank->CanXPlus)
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
    tank->bullet[i].x = tank->x + 20*(cosf(tank->deg));
    tank->bullet[i].y = tank->y + 20*(sinf(tank->deg));
    tank->bullet[i].TimeAppear = SDL_GetTicks();
    tank->NumOFExitBulls ++;
}

void move_bullet(Bullet* bullet){
    bullet->y += BullStep*(sinf(bullet->deg));
    bullet->x += BullStep*(cosf(bullet->deg));
}