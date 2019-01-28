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
    double x, y, r;
    double TimeAppear , CosDeg , SinDeg;
} Bullet;

typedef struct {
    int x1, y1, x2, y2;
    double Rx1, Ry1, Rx2, Ry2;
    Color Color;
    bool exist;
} Wall;

typedef struct {
    double x ,y , radius;
    double deg;
    SDL_Keycode Up_key , Down_key , Right_Key , Left_Key ,Shoot_Key ;
    keyboard Key;
    bool CanXPlus ,CanYPlus , CanXMinus , CanYMinus;
    Color BodyColor , ConstBodyColor;
    Color InnerColor , ConstInnerColor;
    Color PipeColor , ConstPipeColor;
    Bullet bullet[NumOfBulls];
    int NumOFExitBulls , Score;
    int TimeOfLoss;
    bool canshoot , IsAlive;
} Tank;

typedef struct {
    int x , y , NumOfWalls;
    Wall wall[MaxNumOfWalls];
    Tank tank [NumOfTank];
    int DeathTime;
    bool IsAlive;
} Map;

#endif
