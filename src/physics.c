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