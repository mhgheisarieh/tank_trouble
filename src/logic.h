
#ifndef MAIN_C_LOGIC_H
#define MAIN_C_LOGIC_H

#include "struct.h"

void Logics (Map* map);
bool IsDotInWall (Map* map , int x , int y);
bool IsTankInWall (Map* map , Tank* tank);
bool CanXPlus (Map* map , Tank* tank);
bool CanXMinus (Map* map , Tank* tank);
bool CanYPlus (Map* map , Tank* tank);
bool CanYMinus (Map* map , Tank* tank);
bool CanDegPlus (Map* map , Tank* tank);
bool CanDegMinus (Map* map , Tank* tank);
#endif //MAIN_C_LOGIC_H
