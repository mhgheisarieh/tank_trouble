//In the name of Allah

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "struct.h"
#include "startofgame.h"
#include "view.h"
#include "events.h"
#include "Buttons.h"

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Alter Tank-Main Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 800, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    FirstPage FirstPage;
    DefinitionOfButtons (&FirstPage);
    while (1) {
        int start_ticks = SDL_GetTicks();
        handleEventsOfFirstMenu(&FirstPage);
        if (FirstPage.Action != None){
            Quit(renderer, window);
            break;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        DrawButtons (renderer , &FirstPage);
        WriteAbouts (renderer);
        SDL_RenderPresent(renderer);
        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }
    DoAction (FirstPage.Action);
}