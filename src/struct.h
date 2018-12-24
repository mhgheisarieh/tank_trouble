#ifndef MAIN_C_STRUCT_H
#define MAIN_C_STRUCT_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include "constants.h"

typedef struct {
    bool Up_key , Down_key , Right_Key , Left_Key;
}keyboard;

typedef struct {
    int r ,g ,b , a;
} Color;

typedef struct {
    int Exist;
    Sint16 x, y, r;
    double deg, TimeAppear;
} Bullet;

typedef struct {
    int x1, y1, x2, y2;
    double Rx1, Ry1, Rx2, Ry2;
    Color Color;
    bool exist;
} Wall;

typedef struct {
    Sint16 x ,y , radius;
    double deg ;
    SDL_Keycode Up_key , Down_key , Right_Key , Left_Key ,Shoot_Key ;
    keyboard Key;
    Color Color;
    Bullet bullet[NumOfBulls];
    int NumOFExitBulls;
} Tank;

typedef struct {
    int x , y;
    Wall wall[MaxNumOfWalls];
    Tank tank [NumOfTank];
} Map;

#endif
