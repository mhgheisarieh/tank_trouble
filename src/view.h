
#ifndef MAIN_C_VIEW_H
#define MAIN_C_VIEW_H

#include "struct.h"
#include <stdbool.h>

void DrawMap (SDL_Renderer* renderer ,Map* map);
void DrawTank  (SDL_Renderer* renderer , Tank* tank);
void DrawTanks (SDL_Renderer* renderer ,Map* map);
void DrawBullet (SDL_Renderer* renderer, Bullet* bullet);
void DrawBullets (SDL_Renderer* renderer, Map* map);
void DrawWalls (SDL_Renderer* renderer, Wall* wall);
void DrawScores (SDL_Renderer*, Map* map);
void DrawButtons (SDL_Renderer* renderer, FirstPage* FirstPage);
void WriteAbouts (SDL_Renderer* renderer);
void Quit (SDL_Renderer* renderer ,  SDL_Window* window);

#endif //MAIN_C_VIEW_H
