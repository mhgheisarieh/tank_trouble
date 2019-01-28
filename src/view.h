
#ifndef MAIN_C_VIEW_H
#define MAIN_C_VIEW_H

#include "struct.h"
#include <stdbool.h>

void DrawTank  (SDL_Renderer* renderer , Tank* tank);
void DrawTanks (SDL_Renderer* renderer ,Tank* tank);
void DrawBullets (SDL_Renderer* renderer, Tank* tank);
void DrawWalls (SDL_Renderer* renderer, Wall* wall);
void DrawBullet (SDL_Renderer* renderer, Bullet* bullet);
void DrawScores (SDL_Renderer*, Tank* tank);
bool IsAliveBullet (Bullet* bullet);
void Quit (SDL_Renderer* renderer ,  SDL_Window* window);
void DrawMap (SDL_Renderer* renderer ,Map* map);

#endif //MAIN_C_VIEW_H
