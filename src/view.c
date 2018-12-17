#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "view.h"
#include "struct.h"

const int step = 5;
void moveTank(SDL_Keycode key, double* tank_x, double* tank_y) {
    switch (key) {
        case SDLK_UP:
            *tank_y -= step;
            break;
        case SDLK_DOWN:
            *tank_y += step;
            break;
        case SDLK_RIGHT:
            *tank_x += step;
            break;
        case SDLK_LEFT:
            *tank_x -= step;
            break;
    }
}

int handleEvents(double* tank_x, double* tank_y) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return 12345;
        if (event.type == SDL_KEYDOWN)
            moveTank(event.key.keysym.sym , tank_x, tank_y);
    }
}


void init_window(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Alter Tank", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Tank Tank1;
    Tank1.x = 500;
    Tank1.y = 500;
    double tank_radius = 20;
    const double FPS = 30;
    while (1) {
        int start_ticks = SDL_GetTicks();
        if (handleEvents(&(Tank1.x), &(Tank1.y)) == 12345) break;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        filledCircleRGBA(renderer, Tank1.x, Tank1.y, tank_radius, 230, 25, 25, 255);
        filledCircleRGBA(renderer, Tank1.x, Tank1.y, tank_radius/2, 20, 20, 20, 255);
        filledCircleRGBA(renderer, Tank1.x, Tank1.y, tank_radius/4, 230, 25, 25, 255);
        thickLineRGBA(renderer,Tank1.x, Tank1.y, Tank1.x + 40 , Tank1.y , 10 , 230 , 25, 25 , 255);
        SDL_RenderPresent(renderer);
        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

