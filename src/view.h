
#ifndef MAIN_C_VIEW_H
#define MAIN_C_VIEW_H

#include "struct.h"
#include <stdbool.h>

int handleEvents(Map* map);
void DrawTanks (SDL_Renderer* renderer , Tank tank[]);
void DrawBullets (SDL_Renderer* renderer, Tank tank[]);
void DrawWalls (SDL_Renderer* renderer, Wall* wall);
void DrawBullet (SDL_Renderer* renderer, Bullet* bullet);
bool IsAliveBullet (Bullet* bullet);
void Quit (SDL_Renderer* renderer ,  SDL_Window* window);
void DrawMap (Map* map);

#endif //MAIN_C_VIEW_H
