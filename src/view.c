#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "view.h"
#include "physics.h"

int handleEvents(Tank* tank) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        for (int i=0; i<NumOfTank; i++){
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == (tank+i)->Down_key)
                    (tank+i)->Key.Down_key = 1;
                if (event.key.keysym.sym == (tank+i)->Up_key)
                    (tank+i)->Key.Up_key = 1;
                if (event.key.keysym.sym == (tank+i)->Left_Key)
                    (tank+i)->Key.Left_Key = 1;
                if (event.key.keysym.sym == (tank+i)->Right_Key)
                    (tank+i)->Key.Right_Key = 1;
                if (event.key.keysym.sym == (tank+i)->Shoot_Key){
                    fire(tank+i);
                }
                moveTank((tank+i));
                turnTank((tank+i));
            }
            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == (tank+i)->Down_key)
                    (tank+i)->Key.Down_key = 0;
                if (event.key.keysym.sym == (tank+i)->Up_key)
                    (tank+i)->Key.Up_key = 0;
                if (event.key.keysym.sym == (tank+i)->Left_Key)
                    (tank+i)->Key.Left_Key = 0;
                if (event.key.keysym.sym == (tank+i)->Right_Key)
                    (tank+i)->Key.Right_Key = 0;
                moveTank(tank+i);
                turnTank(tank+i);
            }
        }
        if (event.window.event==SDL_WINDOWEVENT_CLOSE)
            return 12345;
    }
    for (int i=0; i<NumOfTank; i++)
        for (int j=0; j<NumOfBulls; j++)
            if ((tank+i)->bullet[j].Exist)
                move_bullet(&(tank+i)->bullet[j]);
}

void DrawTanks (SDL_Renderer* renderer , Tank* tank) {
    for (int i = 0; i < NumOfTank; i++) {
        filledCircleRGBA(renderer, (tank+i)->x, (tank+i)->y, (tank+i)->radius, (tank+i)->Color.r, (tank+i)->Color.g, (tank+i)->Color.b, (tank+i)->Color.a);
        filledCircleRGBA(renderer, (tank+i)->x, (tank+i)->y, (tank+i)->radius / 1.5, 0, 0, 0, 255);
        filledCircleRGBA(renderer, (tank+i)->x, (tank+i)->y, (tank+i)->radius / 4, (tank+i)->Color.r, (tank+i)->Color.g, (tank+i)->Color.b, (tank+i)->Color.a);
        thickLineRGBA(renderer, (tank+i)->x, (tank+i)->y, (tank+i)->x + (30 * cosf((tank+i)->deg)), (tank+i)->y +(30 * sinf((tank+i)->deg)), (tank+i)->radius / 4, (tank+i)->Color.r, (tank+i)->Color.g, (tank+i)->Color.b, (tank+i)->Color.a);
    }
}

void Quit (SDL_Renderer* renderer ,  SDL_Window* window){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void DrawBullets (SDL_Renderer* renderer, Tank tank[]){
    for (int i = 0; i < NumOfTank; i++)
        for (int j = 0; j < NumOfBulls; j++)
            if((tank + i)->bullet[j].Exist){
                Draw_Bullet(renderer, &((tank+i)->bullet[j]));
                if (!IsAliveBullet (&((tank+i)->bullet[j]))){
                    (tank+i)->NumOFExitBulls --;
                }
            }
}

void Draw_Bullet (SDL_Renderer* renderer, Bullet* bullet){
    filledCircleRGBA(renderer, bullet->x, bullet->y, 3, 0, 0, 0, 255);
}

bool IsAliveBullet (Bullet* bullet){
    if ((SDL_GetTicks()-(bullet->TimeAppear))>TimeOfBull) {
        bullet->Exist = 0;
        return 0;
    }
    return 1;
}