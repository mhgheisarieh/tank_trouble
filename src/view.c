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
    DrawTanks (renderer , map);
    DrawBullets (renderer, map);
    DrawWalls (renderer, map->wall);
    DrawScores (renderer, map);
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

void DrawTanks (SDL_Renderer* renderer , Map* map) {
    for (int i = 0; i < map->NumOfTanks; i++) {
        if (map->tank[i].IsAlive) continue;
            DrawTank(renderer , &map->tank[i]);
    }
    for (int i = 0; i < map->NumOfTanks; i++) {
        if (!map->tank[i].IsAlive) continue;
        DrawTank(renderer , &map->tank[i]);
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

void DrawBullets (SDL_Renderer* renderer, Map* map){
    for (int i = 0; i < map->NumOfTanks; i++)
        for (int j = 0; j < NumOfBulls; j++)
            if(map->tank[i].bullet[j].Exist){
                DrawBullet(renderer, &map->tank[i].bullet[j]);
                if (!IsAliveBullet (&map->tank[i].bullet[j])){
                    map->tank[i].NumOFExitBulls --;
                }
            }
}

void DrawBullet (SDL_Renderer* renderer, Bullet* bullet){
    filledCircleRGBA(renderer, (Sint16) bullet->x,  (Sint16) bullet->y, 3, 0, 0, 0, 255);
}

void DrawScores (SDL_Renderer* renderer, Map* map){
    for (int i=0; i< map->NumOfTanks; i++){
        int y = (1000 / (2 * map->NumOfTanks + 2)) * (2 * i + 2);
        filledCircleRGBA(renderer, 1100, (Sint16) y , 40,
                (Uint8) map->tank[i].ConstBodyColor.r,
                (Uint8) map->tank[i].ConstBodyColor.g,
                (Uint8) map->tank[i].ConstBodyColor.b,
                (Uint8) map->tank[i].ConstBodyColor.a);
        filledCircleRGBA(renderer, 1100, (Sint16) y, 20,
                (Uint8) map->tank[i].ConstInnerColor.r,
                (Uint8) map->tank[i].ConstInnerColor.g,
                (Uint8) map->tank[i].ConstInnerColor.b,
                (Uint8) map->tank[i].ConstInnerColor.a);
        thickLineRGBA(renderer, 1100 , (Sint16)(y + 25) , 1100 , (Sint16)(y +50) , 10 ,
                (Uint8) map->tank[i].ConstPipeColor.r,
                (Uint8) map->tank[i].ConstPipeColor.g,
                (Uint8) map->tank[i].ConstPipeColor.b,
                (Uint8) map->tank[i].ConstPipeColor.a);
        char ScoreString [20] = "Score: ";
        sprintf(ScoreString + 7 , "%d" , map->tank[i].Score);
        int n = (int) strlen(ScoreString);
        SDL_RenderSetScale(renderer , 2 ,2);
        stringRGBA(renderer , (Sint16)((1100 - n * 8)/2)  , (Sint16) ((y + 70)/2) ,  ScoreString , 0 , 0 , 0 ,255);
        SDL_RenderSetScale(renderer , 1,1);
    }
}

void DrawButtons (SDL_Renderer* renderer, FirstPage* FirstPage){
    for (int i=0; i<NumOfButtons; i++){
        if (i == FirstPage->SelectedButtonNum) continue;
        thickLineRGBA(renderer,  (Sint16) FirstPage->buttons[i].x1 ,
                                 (Sint16) FirstPage->buttons[i].y ,
                                 (Sint16) FirstPage->buttons[i].x2 ,
                                 (Sint16) FirstPage->buttons[i].y , ButtonWide ,
                                 (Uint8) FirstPage->ButtonColor.r ,
                                 (Uint8) FirstPage->ButtonColor.g ,
                                 (Uint8) FirstPage->ButtonColor.b ,
                                 (Uint8) FirstPage->ButtonColor.a);
    }
    thickLineRGBA(renderer,  (Sint16) FirstPage->buttons[FirstPage->SelectedButtonNum].x1 ,
                  (Sint16) FirstPage->buttons[FirstPage->SelectedButtonNum].y ,
                  (Sint16) FirstPage->buttons[FirstPage->SelectedButtonNum].x2 ,
                  (Sint16) FirstPage->buttons[FirstPage->SelectedButtonNum].y , ButtonWide ,
                  (Uint8) FirstPage->SelectedColor.r ,
                  (Uint8) FirstPage->SelectedColor.g ,
                  (Uint8) FirstPage->SelectedColor.b ,
                  (Uint8) FirstPage->SelectedColor.a);
    for (int i=0; i<NumOfButtons; i++) {
        SDL_RenderSetScale(renderer , 1.5 ,1.5);
        stringRGBA(renderer, (Sint16)((200 - 6 * strlen(FirstPage->buttons[i].text))/1.5),
                   (Sint16)((FirstPage->buttons[i].y)/1.5), FirstPage->buttons[i].text, 0, 0, 0, 255);
        SDL_RenderSetScale(renderer , 1 ,1);
    }
}

void WriteAbouts (SDL_Renderer* renderer){
    stringRGBA(renderer, 20 , 720 ,"Play 3v3: 3 Key     Play 2v2: 2 Key" , 0 , 0 ,0 ,255);
    stringRGBA(renderer, 20 , 740 ,"Load Game: L        Save Game: S" , 0 , 0 ,0 ,255);
    stringRGBA(renderer, 20 , 760 ,"Preference: P       About Game: F1" , 0 , 0 ,0 ,255);
    stringRGBA(renderer, 20 , 780 ,"Quit: Q" , 0 , 0 ,0 ,255);
}

void Quit (SDL_Renderer* renderer ,  SDL_Window* window){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}