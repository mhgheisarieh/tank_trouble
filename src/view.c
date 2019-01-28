#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "view.h"
#include "physics.h"
#include "logic.h"

void DrawMap (SDL_Renderer* renderer ,Map* map){
    DrawTanks (renderer , map->tank);
    DrawBullets (renderer, map->tank);
    DrawWalls (renderer, map->wall);
    DrawScores (renderer, map->tank);
}

void DrawTank  (SDL_Renderer* renderer , Tank* tank) {
    filledCircleRGBA(renderer, (Sint16)(tank)->x,(Sint16)(tank)->y,(Sint16) (tank)->radius,
                     (Uint8)(tank)->BodyColor.r,
                     (Uint8)(tank)->BodyColor.g,
                     (Uint8)(tank)->BodyColor.b,
                     (Uint8)(tank)->BodyColor.a);
    filledCircleRGBA(renderer, (Sint16)(tank)->x,(Sint16)(tank)->y,(Sint16) ((tank)->radius / 2),
                     (Uint8)(tank)->InnerColor.r,
                     (Uint8)(tank)->InnerColor.g,
                     (Uint8)(tank)->InnerColor.b,
                     (Uint8)(tank)->InnerColor.a);
    thickLineRGBA(renderer,(Sint16)((tank)->x + (PipeLength * cosf((float)(tank)->deg)) / 1.8),
                  (Sint16)((tank)->y + (PipeLength * sinf((float)(tank)->deg)) / 1.8),
                  (Sint16)((tank)->x + (PipeLength * cosf((float)(tank)->deg))),
                  (Sint16)((tank)->y +(PipeLength * sinf((float)(tank)->deg))),
                  (Uint8)((tank)->radius / 4),
                  (Uint8)(tank)->PipeColor.r,
                  (Uint8)(tank)->PipeColor.g,
                  (Uint8)(tank)->PipeColor.b,
                  (Uint8)(tank)->PipeColor.a);
}

void DrawTanks (SDL_Renderer* renderer , Tank* tank) {
    for (int i = 0; i < NumOfTank; i++) {
        if ((tank+i)->IsAlive) continue;
            DrawTank(renderer , (tank+i));
    }
    for (int i = 0; i < NumOfTank; i++) {
        if (!(tank+i)->IsAlive) continue;
        DrawTank(renderer , (tank+i));
    }
}

void DrawWalls (SDL_Renderer* renderer, Wall* wall){
    int i =0;
    while ((wall+i)->exist == 1){
        thickLineRGBA(renderer,  (Sint16)(wall+i)->Rx1 ,  (Sint16)(wall+i)->Ry1 ,  (Sint16)(wall+i)->Rx2 ,  (Sint16)(wall+i)->Ry2 ,
                       3 , wall->Color.r , wall->Color.g , wall->Color.b , wall->Color.a);
        i++;
    }
}

void DrawBullets (SDL_Renderer* renderer, Tank* tank){
    for (int i = 0; i < NumOfTank; i++)
        for (int j = 0; j < NumOfBulls; j++)
            if((tank + i)->bullet[j].Exist){
                DrawBullet(renderer, &((tank+i)->bullet[j]));
                if (!IsAliveBullet (&((tank+i)->bullet[j]))){
                    (tank+i)->NumOFExitBulls --;
                }
            }
}

void DrawBullet (SDL_Renderer* renderer, Bullet* bullet){
    filledCircleRGBA(renderer, (Sint16) bullet->x,  (Sint16) bullet->y, 3, 0, 0, 0, 255);
}

void DrawScores (SDL_Renderer* renderer, Tank* tank){
    for (int i=0; i<NumOfTank; i++){
        int y = (1000 / (2 * NumOfTank + 2)) * (2 * i + 2);
        filledCircleRGBA(renderer, 1100, (Sint16) y , 40,
                (Uint8)(tank+i)->ConstBodyColor.r,
                (Uint8)(tank+i)->ConstBodyColor.g,
                (Uint8)(tank+i)->ConstBodyColor.b,
                (Uint8)(tank+i)->ConstBodyColor.a);
        filledCircleRGBA(renderer, 1100, (Sint16) y, 20,
                (Uint8)(tank+i)->ConstInnerColor.r,
                (Uint8)(tank+i)->ConstInnerColor.g,
                (Uint8)(tank+i)->ConstInnerColor.b,
                (Uint8)(tank+i)->ConstInnerColor.a);
        thickLineRGBA(renderer, 1100 , (Sint16)(y + 25) , 1100 , (Sint16)(y +50) , 10 ,
                (Uint8)(tank+i)->ConstPipeColor.r,
                (Uint8)(tank+i)->ConstPipeColor.g,
                (Uint8)(tank+i)->ConstPipeColor.b,
                (Uint8)(tank+i)->ConstPipeColor.a);
        char ScoreString [20] = "Score: ";
        sprintf(ScoreString + 7 , "%d" , (tank+i)->Score);
        int n = (int) strlen(ScoreString);
        SDL_RenderSetScale(renderer , 2 ,2);
        stringRGBA(renderer , (Sint16)((1100 - n * 8)/2)  , (Sint16) ((y + 70)/2) ,  ScoreString , 0 , 0 , 0 ,255);
        SDL_RenderSetScale(renderer , 1,1);
    }
}

void Quit (SDL_Renderer* renderer ,  SDL_Window* window){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool IsAliveBullet (Bullet* bullet){
    if ((SDL_GetTicks()-(bullet->TimeAppear))>TimeOfBull) {
        bullet->Exist = 0;
        return 0;
    }
    return 1;
}
