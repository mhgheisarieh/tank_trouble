
#ifndef MAIN_C_PHYSICS_H
#define MAIN_C_PHYSICS_H

#include "struct.h"
void moveTank(Tank* tank);
void turnTank(Tank* tank);
void fire(Tank* tank , int GameTime);
void move_bullet(Bullet* bullet , Map* map);
int IsPlus(double i);
void TMPMoveBullet (Bullet* bullet);
void Physics (Map* map);

#endif //MAIN_C_PHYSICS_H
