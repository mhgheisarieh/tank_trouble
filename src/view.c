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
    if (tank->FullDied) return;
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
        if (map->tank[i].IsAlive || map->tank[i].FullDied) continue;
            DrawTank(renderer , &map->tank[i]);
    }
    for (int i = 0; i < map->NumOfTanks; i++) {
        if (!map->tank[i].IsAlive || map->tank[i].FullDied) continue;
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
                if (!IsAliveBullet (map->GameTime , &map->tank[i].bullet[j])){
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

void DrawFirstPage (SDL_Renderer* renderer, FirstPage* FirstPage){
    for (int i=0; i<NumOfMainMenuButtons; i++){
        if (i == FirstPage->SelectedButtonNum) continue;
        roundedBoxRGBA(renderer,  ButtonsX1 , (Sint16) FirstPage->buttons[i].y1 ,
                                  ButtonsX2 , (Sint16) FirstPage->buttons[i].y2 , RoundOfButtons ,
                                  (Uint8) FirstPage->ButtonColor.r ,
                                  (Uint8) FirstPage->ButtonColor.g ,
                                  (Uint8) FirstPage->ButtonColor.b ,
                                  (Uint8) FirstPage->ButtonColor.a);
    }
    roundedBoxRGBA(renderer,  ButtonsX1 , (Sint16) FirstPage->buttons[FirstPage->SelectedButtonNum].y1 ,
                              ButtonsX2 , (Sint16) FirstPage->buttons[FirstPage->SelectedButtonNum].y2 , RoundOfButtons ,
                             (Uint8) FirstPage->SelectedColor.r ,
                             (Uint8) FirstPage->SelectedColor.g ,
                             (Uint8) FirstPage->SelectedColor.b ,
                             (Uint8) FirstPage->SelectedColor.a);
    for (int i=0; i<NumOfMainMenuButtons; i++) {
        SDL_RenderSetScale(renderer , 1.5 ,1.5);
        stringRGBA(renderer, (Sint16)((600 - 6 * strlen(FirstPage->buttons[i].text))/1.5),
                   (Sint16)((FirstPage->buttons[i].y1+ FirstPage->buttons[i].y2)/3), FirstPage->buttons[i].text, 0, 0, 0, 255);
        SDL_RenderSetScale(renderer , 1 ,1);
    }
    SDL_RenderSetScale(renderer , 2.5,2.5);
    stringRGBA(renderer, 20 , 20 ,"Use Up and Down Key and Enter key or Hotkeys to select!" , 0 , 0 ,0 ,255);
    SDL_RenderSetScale(renderer , 2 ,2 );
    stringRGBA(renderer, 20 , 700/2 ,"Play 2v2: 2 Key" , 0 , 0 ,0 ,255);
    stringRGBA(renderer, 20 , 760/2 ,"Play 3v3: 3 Key" , 0 , 0 ,0 ,255);
    stringRGBA(renderer, 20 , 820/2 ,"Load Game: L" , 0 , 0 ,0 ,255);
    stringRGBA(renderer, 20 , 880/2 ,"About Game: F1" , 0 , 0 ,0 ,255);
    stringRGBA(renderer, 20 , 940/2 ,"Quit: Q" , 0 , 0 ,0 ,255);
    SDL_RenderSetScale(renderer , 1 ,1);
}

void DrawMiddlePage (SDL_Renderer* renderer ,MiddlePage* MiddlePage) {
    roundedBoxRGBA (renderer, 300 , 250, 900, 775, RoundOfButtons ,
            (Uint8) MiddlePage->BackgroundColor.r ,
            (Uint8) MiddlePage->BackgroundColor.g ,
            (Uint8) MiddlePage->BackgroundColor.b ,
            (Uint8) MiddlePage->BackgroundColor.a);
    for (int i=0; i<NumOfMiddleMenuButtons; i++){
        if (i == MiddlePage->SelectedButtonNum) continue;
        roundedBoxRGBA(renderer,  ButtonsX1 , (Sint16) MiddlePage->buttons[i].y1 ,
                                  ButtonsX2 , (Sint16) MiddlePage->buttons[i].y2 , RoundOfButtons ,
                       (Uint8) MiddlePage->ButtonColor.r ,
                       (Uint8) MiddlePage->ButtonColor.g ,
                       (Uint8) MiddlePage->ButtonColor.b ,
                       (Uint8) MiddlePage->ButtonColor.a);
    }
    roundedBoxRGBA(renderer,  ButtonsX1 , (Sint16) MiddlePage->buttons[MiddlePage->SelectedButtonNum].y1 ,
                              ButtonsX2 , (Sint16) MiddlePage->buttons[MiddlePage->SelectedButtonNum].y2 , RoundOfButtons ,
                   (Uint8) MiddlePage->SelectedColor.r ,
                   (Uint8) MiddlePage->SelectedColor.g ,
                   (Uint8) MiddlePage->SelectedColor.b ,
                   (Uint8) MiddlePage->SelectedColor.a);
    for (int i=0; i<NumOfMiddleMenuButtons; i++) {
        SDL_RenderSetScale(renderer , 1.5 ,1.5);
        stringRGBA(renderer, (Sint16)((600 - 6 * strlen(MiddlePage->buttons[i].text))/1.5),
                   (Sint16)((MiddlePage->buttons[i].y1+ MiddlePage->buttons[i].y2)/3), MiddlePage->buttons[i].text, 0, 0, 0, 255);
        SDL_RenderSetScale(renderer , 1 ,1);
    }
}

void DrawAskPointPage (SDL_Renderer* renderer , NumberBox* numberbox){
    SDL_RenderSetScale(renderer , 2,2);
    stringRGBA(renderer, 80 , 60 ,"Enter the winning point of game: " , 0 , 0 ,0 ,255);
    char point [3];
    sprintf (point ,"%d" , numberbox->number);
    roundedBoxRGBA(renderer, numberbox->x1 , numberbox->y1 , numberbox->x2 , numberbox->y2 , RoundOfNumberBox ,
                    numberbox->Color.r , numberbox->Color.g , numberbox->Color.b , numberbox->Color.a);
    stringRGBA(renderer, 355 , 60 ,point , 0 , 0 ,0 ,255);
    SDL_RenderSetScale(renderer , 1,1);
}

void DrawWinPage (SDL_Renderer* renderer, Map* map){
    char string [30];
    if (map->NumOfTanks == 2)
        roundedBoxRGBA(renderer,  300 , 250, 900, 625 , 20 , 240, 215, 190 , 200);
    if (map->NumOfTanks == 3){
        roundedBoxRGBA(renderer,  300 , 250, 900, 775 , 20 , 240, 215, 190 , 200);
        roundedBoxRGBA(renderer,  325 , 650, 875, 750 , 20 , 25 , 230, 100 , 200);
        SDL_RenderSetScale(renderer , 2.5,2.5);
        sprintf(string , "Score: %d" , map->tank[2].Score);
        stringRGBA(renderer , (Sint16)(350/2.5) , (Sint16)(700/2.5) ,string, 0 ,0 ,0, 255);
        SDL_RenderSetScale(renderer , 1 ,1);
    }
    roundedBoxRGBA(renderer,  325 , 350, 875, 450 , 20 , 250, 0 , 0 , 200);
    roundedBoxRGBA(renderer,  325 , 500, 875, 600 , 20 , 25 , 100, 230 , 200);
    SDL_RenderSetScale(renderer , 2.5,2.5);
    sprintf(string , "Score: %d" , map->tank[0].Score);
    stringRGBA(renderer, (Sint16)(350.0/2.5) , (Sint16)(400.0/2.5) , string ,0 , 0 , 0, 255);
    sprintf(string , "Score: %d" , map->tank[1].Score);
    stringRGBA(renderer, (Sint16)(350.0/2.5) , (Sint16)(550.0/2.5) , string ,0 , 0 , 0, 255);
    stringRGBA(renderer, (Sint16)(380.0/2.5) , (Sint16)(290.0/2.5) , "Press Enter to continue" ,0 , 0 , 0, 255);
    switch (map->WinnerTank){
        case 0:
            stringRGBA(renderer, (Sint16)(700.0/2.5) , (Sint16)(400.0/2.5) , "Winner!" ,0 , 0 , 0, 255);
            break;
        case 1:
            stringRGBA(renderer, (Sint16)(700.0/2.5) , (Sint16)(550.0/2.5) , "Winner!" ,0 , 0 , 0, 255);
            break;
        case 2:
            stringRGBA(renderer, (Sint16)(700.0/2.5) , (Sint16)(700.0/2.5) , "Winner!", 0 , 0 , 0, 255);
            break;
    }
    SDL_RenderSetScale(renderer , 1,1);
}

void Quit (SDL_Renderer* renderer ,  SDL_Window* window){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}