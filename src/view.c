#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "view.h"
#include "physics.h"

int handleEvents(Tank* tank) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return 12345;
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == tank->Down_key)
                tank->Key.Down_key = 1;
            if (event.key.keysym.sym == tank->Up_key)
                tank->Key.Up_key = 1;
            if (event.key.keysym.sym == tank->Left_Key)
                tank->Key.Left_Key = 1;
            if (event.key.keysym.sym == tank->Right_Key)
                tank->Key.Right_Key = 1;
            moveTank(tank);
            turnTank(tank);
        }
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == tank->Down_key)
                tank->Key.Down_key = 0;
            if (event.key.keysym.sym == tank->Up_key)
                tank->Key.Up_key = 0;
            if (event.key.keysym.sym == tank->Left_Key)
                tank->Key.Left_Key = 0;
            if (event.key.keysym.sym == tank->Right_Key)
                tank->Key.Right_Key = 0;
            moveTank(tank);
            turnTank(tank);
        }
    }
}

void DrawTank (SDL_Renderer* renderer , Tank tank[]) {
    for (int i = 0; i < NumOfTank; i++) {
        filledCircleRGBA(renderer, tank[i].x, tank[i].y, tank[i].radius, tank[i].Color.r, tank[i].Color.g, tank[i].Color.b, tank[0].Color.a);
        filledCircleRGBA(renderer, tank[i].x, tank[i].y, tank[i].radius / 1.5, 0, 0, 0, 255);
        filledCircleRGBA(renderer, tank[i].x, tank[i].y, tank[i].radius / 4, tank[i].Color.r, tank[i].Color.g, tank[i].Color.b, tank[i].Color.a);
        thickLineRGBA(renderer, tank[i].x, tank[i].y, tank[i].x + (30 * cos(tank[i].deg)), tank[i].y +(30 * sin(tank[i].deg)), tank[i].radius / 4, tank[i].Color.r, tank[i].Color.g, tank[i].Color.b, tank[i].Color.a);
    }
}

void Quit (SDL_Renderer* renderer ,  SDL_Window* window){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
