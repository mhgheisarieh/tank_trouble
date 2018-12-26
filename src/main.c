//In the name of Allah

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "view.h"
#include "DefinitionOfTanks.h"
#include "maps.h"
#include "physics.h"
#include "logic.h"

#ifdef main
#undef main
#endif

int main(int argc , char* argv[]){
    Map map;
    Definition(&map.tank);
    LoadMap (&map);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Alter Tank", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    while (1) {
        int flag = 1;
        int start_ticks = SDL_GetTicks();
        if (handleEvents(&map) == 12345){
            Quit(renderer, window);
            break;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        DrawTanks (renderer , &map.tank);
        DrawBullets (renderer, &map.tank);
        DrawWalls (renderer, &map.wall);
        SDL_RenderPresent(renderer);
        IsWall(&map);
        for (int i=0 ; i<NumOfTank; i++){
            moveTank(&map.tank[i]);
            turnTank(&map.tank[i]);
        }
        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }
}
