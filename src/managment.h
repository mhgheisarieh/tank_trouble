
#ifndef MAIN_C_MANAGMENT_H
#define MAIN_C_MANAGMENT_H

#include "struct.h"

void CheckBullets (Map* map);
void LossOfTank (Tank* tank , Bullet* bullet);
void CheckGame(Map* map);
void FadeTank (Tank* tank);

#endif //MAIN_C_MANAGMENT_H
