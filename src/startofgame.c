
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "view.h"
#include "newround.h"
#include "maps.h"
#include "physics.h"
#include "logic.h"
#include "events.h"
#include "managment.h"
#include "startofgame.h"
#include "Menus.h"

void StartGame (int NumOfTank , SDL_Renderer* renderer ,  SDL_Window* window){
    Map map;
    map.NumOfTanks = NumOfTank;
    map.Enabled = 1;
    map.WinnerTank = NULL;
    int status  = AskWinPoint (renderer , &map , window);
    if (status == Exit) return;
    for (int i=0; i < map.NumOfTanks; i++) {
        map.tank[i].Score = 0;
    }
    NewRound (&map);
    MiddlePage MiddlePage;
    DefinitionOfMiddleMenu(&MiddlePage);
    int Status;
    while (1) {
        int start_ticks = SDL_GetTicks();
        Status = handleEvents(&map , &MiddlePage );
        if (Status == Exit){
            Quit(renderer, window);
            break;
        } else if (Status == ENDGAME){
            SDL_RenderClear(renderer);
            break;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        map.GameTime = (map.frames - 1) * 20;
        DrawMap(renderer , &map);
        if (map.Enabled){
            map.frames ++;
            Logics(&map);
            Physics(&map);
            CheckGame(&map);
        } else {
            if (map.WinnerTank == NULL)
                DrawMiddlePage (renderer , &MiddlePage);
            else {
                DrawWinPage (renderer, &map);
            }
        }
        SDL_RenderPresent(renderer);
        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }
    if (Status == ENDGAME){
        FirstPage firstPage;
        DefinitionOfMainMenu(&firstPage);
        ManageFirstPage(&firstPage, renderer, window);
    }
}

int AskWinPoint (SDL_Renderer* renderer , Map* map , SDL_Window* window){
    NumberBox numberBox;
    DefinitionOfAskPointNumberBox(&numberBox);
    while (1) {
        int start_ticks = SDL_GetTicks();
        int Status = handleEventsOfNumberBox(&numberBox);
        if (Status == Exit){
            Quit(renderer, window);
            return Exit;
        } else if (Status == ENTER){
            map->WinPoint = numberBox.number;
            return 0;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        DrawAskPointPage(renderer , &numberBox);
        SDL_RenderPresent(renderer);
        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }
}

void DefinitionOfAskPointNumberBox(NumberBox* numberBox){
    numberBox->number = 1;
    numberBox->x1 = 350;
    numberBox->x2 = 384;
    numberBox->y1 = 52;
    numberBox->y2 = 72;
    numberBox->Color.a = 255;
    numberBox->Color.r = 250;
    numberBox->Color.g = 225;
    numberBox->Color.b = 200;
}

void ManageFirstPage (FirstPage* FirstPage , SDL_Renderer* renderer, SDL_Window* window){
    while (1) {
        int start_ticks = SDL_GetTicks();
        handleEventsOfFirstMenu(FirstPage);
        if (FirstPage->Action != None){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            break;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        DrawFirstPage (renderer , FirstPage);
        SDL_RenderPresent(renderer);
        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }
    switch (FirstPage->Action){
        case Play2v2:
            StartGame(2 ,renderer , window);
            break;
        case Play3v3:
            StartGame(3 ,renderer , window);
            break;
        case quit:
            Quit(renderer, window);
            break;
    }
}