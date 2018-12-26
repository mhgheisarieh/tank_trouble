
#ifndef MAIN_C_LOGIC_H
#define MAIN_C_LOGIC_H

#include "struct.h"

void IsWall (Map* map);
bool CanXPlus (Map* map , Tank* tank);
bool CanXMinus (Map* map , Tank* tank);
bool CanYPlus (Map* map , Tank* tank);
bool CanYMinus (Map* map , Tank* tank);
#endif //MAIN_C_LOGIC_H
