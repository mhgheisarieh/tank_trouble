
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

void StartGame (int NumOfTank){
    gfxPrimitivesSetFont(NULL,0,0);
    Map map;
    map.NumOfTanks = NumOfTank;
    for (int i=0; i < map.NumOfTanks; i++) {
        map.tank[i].Score = 0;
    }
    NewRound (&map);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Alter Tank", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1000, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    while (1) {
        int start_ticks = SDL_GetTicks();
        if (handleEvents(&map) == Exit){
            Quit(renderer, window);
            break;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        DrawMap(renderer , &map);
        SDL_RenderPresent(renderer);
        Logics(&map);
        Physics(&map);
        CheckGame(&map);
        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }
}