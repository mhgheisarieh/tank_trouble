
#ifndef MAIN_C_VIEW_H
#define MAIN_C_VIEW_H

#include "struct.h"

int handleEvents(Tank* tank);
void DrawTank (SDL_Renderer* renderer , Tank tank[]);
void Quit (SDL_Renderer* renderer ,  SDL_Window* window);
#endif //MAIN_C_VIEW_H
