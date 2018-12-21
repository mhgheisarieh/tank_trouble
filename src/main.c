//In the name of Allah

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "view.h"
#include "DefinitionOfTanks.h"

#ifdef main
#undef main
#endif

int main(int argc , char* argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Alter Tank", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Tank tank[NumOfTank];
    Definition(&tank);

    const double FPS = 20;
    while (1) {
        int flag = 1;
        int start_ticks = SDL_GetTicks();
        if (handleEvents(&tank[0]) == 12345){
            Quit(renderer, window);
            break;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        DrawTanks (renderer , &tank[0]);
        DrawBullets (renderer, &tank[0]);
        SDL_RenderPresent(renderer);
        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }
}
