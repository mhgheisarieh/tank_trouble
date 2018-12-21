
#ifndef MAIN_C_VIEW_H
#define MAIN_C_VIEW_H

#include "struct.h"
#include <stdbool.h>

int handleEvents(Tank* tank);
void DrawTanks (SDL_Renderer* renderer , Tank tank[]);
void DrawBullets (SDL_Renderer* renderer, Tank tank[]);
void Draw_Bullet (SDL_Renderer* renderer, Bullet* bullet);
bool IsAliveBullet (Bullet* bullet);
void Quit (SDL_Renderer* renderer ,  SDL_Window* window);

#endif //MAIN_C_VIEW_H
