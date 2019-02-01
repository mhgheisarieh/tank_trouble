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
    int Exist , TimeAppear ;
    double x, y, r;
    double CosDeg , SinDeg;
} Bullet;

typedef struct {
    int x1, y1, x2, y2;
    double Rx1, Ry1, Rx2, Ry2;
    Color Color;
    bool exist;
} Wall;

typedef struct {
    double x ,y , radius ,deg;
    SDL_Keycode Up_key , Down_key , Right_Key , Left_Key ,Shoot_Key ;
    keyboard Key;
    bool CanXPlus ,CanYPlus , CanXMinus , CanYMinus;
    Color BodyColor , ConstBodyColor;
    Color InnerColor , ConstInnerColor;
    Color PipeColor , ConstPipeColor;
    Bullet bullet[NumOfBulls];
    int NumOFExitBulls , Score ;
    bool canshoot , IsAlive ,FullDied;
} Tank;

typedef struct {
    int NumOfTanks;
    int x , y , NumOfWalls;
    int WinPoint;
    Wall wall[MaxNumOfWalls];
    Tank tank [3];
    int WinnerTank , DeathTime ,GameTime , frames;
    bool IsAlive , Enabled;
} Map;

enum Actions {Play3v3 , Play2v2  , load, save ,setting , about ,quit ,None , resume , Back };

typedef struct {
    int y1 , y2;
    char text [50];
    enum Actions action;
} Button;

typedef struct {
    Button buttons[NumOfMainMenuButtons];
    int SelectedButtonNum;
    Color ButtonColor;
    Color SelectedColor;
    enum Actions  Action;
}FirstPage;

typedef struct {
    Button buttons[NumOfMiddleMenuButtons];
    int SelectedButtonNum;
    Color ButtonColor;
    Color SelectedColor;
    Color BackgroundColor;
    enum Actions Action;
}MiddlePage;

typedef struct {
    int number;
    Sint16 x1, x2 ,y1 ,y2;
    Color Color;
}NumberBox;

enum PowerUpType {FragBomb , Mine , Laser , NoPowerUp};

typedef struct {
    int x ,y;
    enum PowerUpType PowerUpType;
}PowerUp;

#endif
