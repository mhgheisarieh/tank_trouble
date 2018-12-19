//In the name of Allah

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "view.h"

#ifdef main
#undef main
#endif

int main(int argc , char* argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Alter Tank", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Tank tank[NumOfTank];

    //Definition of tank[0]:
    tank[0].x = 500;
    tank[0].y = 500;
    tank[0].deg = 0;
    tank[0].radius = 15;
    tank[0].Color.r = 230;
    tank[0].Color.g = 25;
    tank[0].Color.b = 25;
    tank[0].Color.a = 255;
    tank[0].Down_key =SDLK_DOWN;
    tank[0].Up_key =SDLK_UP;
    tank[0].Left_Key =SDLK_LEFT;
    tank[0].Right_Key =SDLK_RIGHT;
    tank[0].Key.Right_Key = 0;
    tank[0].Key.Up_key = 0;
    tank[0].Key.Left_Key = 0;
    tank[0].Key.Down_key = 0;

    const double FPS = 200;
    while (1) {
        int flag = 1;
        int start_ticks = SDL_GetTicks();
        for (int i=0; i<NumOfTank; i++)
            if (handleEvents(&tank[i]) == 12345) (flag = 0);
        if (flag == 0) {
            Quit (renderer ,window);
            break;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        for (int i=0; i<NumOfTank; i++)
            DrawTank (renderer , &tank[i]);
        SDL_RenderPresent(renderer);
        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }
}
