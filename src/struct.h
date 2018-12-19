#ifndef MAIN_C_STRUCT_H
#define MAIN_C_STRUCT_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdbool.h>

#define Step 3
#define NumOfTank 1
#define DegStep 0.05
typedef struct {
    bool Up_key , Down_key , Right_Key , Left_Key;
}keyboard;

typedef struct {
    int r ,g ,b , a;
} Color;

typedef struct {
    Sint16 x ,y , radius;
    double deg ;
    SDL_Keycode Up_key , Down_key , Right_Key , Left_Key;
    keyboard Key;
    Color Color;
} Tank;

#endif
