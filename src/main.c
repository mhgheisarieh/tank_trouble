//In the name of Allah

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "startofgame.h"
#include "view.h"
#include "events.h"

int main(){
    /*SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Alter Tank-Main Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 400, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);*/
    StartGame();
    /*while (1) {
        int start_ticks = SDL_GetTicks();
        if (handleEventsOfFirstMenu() == Exit){
            Quit(renderer, window);
            break;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }*/
}