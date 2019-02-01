#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "physics.h"
#include "logic.h"

void Physics (Map* map){
    for (int i=0 ; i<map->NumOfTanks; i++){
        moveTank(&map->tank[i]);
        turnTank(&map->tank[i]);
        IsMined (map , &map->tank[i]);
        for (int j=0; j<NumOfBulls; j++)
            if (map->tank[i].bullet[j].Exist)
                move_bullet(&map->tank[i].bullet[j] , map);
    }
}

int IsPlus(double i){
    if (i>=0) return 1;
    return 0;
}

void IsMined (Map* map, Tank* tank){
    if (map->frames - tank->TimeOfMinned > TimeOfTankMined * Second) tank->IsMined =0;
    if (tank->IsMined) return;
    for (int i=0; i<3; i++){
        double distance = sqrt ((tank->x - map->powerUP[i].x) * (tank->x - map->powerUP[i].x)
                                + (tank->y - map->powerUP[i].y) * (tank->y - map->powerUP[i].y));
        if (distance < 45){
            map->powerUP[i].enabled = 0;
            tank->IsMined = 1;
            tank->TimeOfMinned = map->frames;
        }
    }
}

void moveTank(Tank* tank) {
    if (!tank->IsAlive) return;
    if (tank->Key.Up_key && tank->Key.Down_key) return;
    if (tank->Key.Up_key){
        if (IsPlus(sin(tank->deg))){
            if (tank->CanYPlus)
                tank->y = (Sint16) (tank->y + Step *(sinf((float) tank->deg)));
        } else {
            if (tank->CanYMinus)
                tank->y = (Sint16) (tank->y + Step *(sinf((float) tank->deg)));
        }
        if (IsPlus(cos(tank->deg))){
            if (tank->CanXPlus)
                tank->x = (Sint16) (tank->x + Step *(cosf((float) tank->deg)));
        } else {
            if (tank->CanXMinus)
                tank->x = (Sint16) (tank->x + Step *(cosf((float) tank->deg)));
        }
    }
    if (tank->Key.Down_key){
        if (IsPlus(sin(tank->deg))){
            if (tank->CanYMinus)
                tank->y = (Sint16) (tank->y - Step*(sinf((float) tank->deg)));
        } else {
            if (tank->CanYPlus)
                tank->y = (Sint16) (tank->y - Step*(sinf((float) tank->deg)));
        }
        if (IsPlus(cos(tank->deg))){
            if (tank->CanXMinus)
                tank->x = (Sint16) (tank->x - Step*(cosf((float) tank->deg)));
        } else {
            if (tank->CanXPlus)
                tank->x = (Sint16) (tank->x - Step*(cosf((float) tank->deg)));
        }
    }
}

void turnTank(Tank* tank){
    if (!tank->IsAlive) return;
    if (tank->Key.Right_Key)
        tank->deg += DegStep;
    if (tank->Key.Left_Key)
        tank->deg -= DegStep;
}

void fire(Tank* tank , int GameTime){
    if (!tank->IsAlive) return;
    if (tank->NumOFExitBulls == NumOfBulls) return;
    if (tank->IsMined) {
        Minnig (tank , GameTime);
        return;
    }
    int i;
    for (i=0; i<NumOfBulls; i++)
        if (tank->bullet[i].Exist==0)
            break;
    tank->bullet[i].Exist =1;
    tank->bullet[i].CosDeg = cosf((float)tank->deg);
    tank->bullet[i].SinDeg = sinf((float)tank->deg);
    tank->bullet[i].x = tank->x + PipeLength*(cosf((float)tank->deg))*0.9;
    tank->bullet[i].y = tank->y + PipeLength*(sinf((float)tank->deg))*0.9;
    tank->bullet[i].TimeAppear = GameTime;
    tank->NumOFExitBulls ++;
}

void Minnig (Tank* tank , int GameTime){
    int i;
    for (i=0; i<10; i++){
        if (tank->mine[i].Enabled==0){
            tank->mine[i].Enabled =1;
            break;
        }
        if (i==9) return;
    }
    tank->mine[i].x = (int)tank->x;
    tank->mine[i].y = (int)tank->y;
    tank->mine[i].TimeOfMining = GameTime/20 +1;
}

void move_bullet(Bullet* bullet , Map* map){
    Bullet tmp;
    tmp = *bullet;
    TMPMoveBullet (&tmp);
    for (int WallNum = 0; WallNum < map->NumOfWalls ; WallNum++){
        if(map->wall[WallNum].x1 == map->wall[WallNum].x2) {

            if(bullet->y >= map->wall[WallNum].Ry1 -5 && bullet->y <= map->wall[WallNum].Ry2 +5) {
                if((tmp.x <= map->wall[WallNum].Rx1 && bullet->x >= map->wall[WallNum].Rx1)
                || (tmp.x >= map->wall[WallNum].Rx1 && bullet->x <= map->wall[WallNum].Rx1)){
                    bullet->CosDeg *= -1;
                }
            }
        } else if(map->wall[WallNum].y1 == map->wall[WallNum].y2) {
            if(bullet->x >= map->wall[WallNum].Rx1 -5 && bullet->x <= map->wall[WallNum].Rx2 +5) {
                if((tmp.y <= map->wall[WallNum].Ry1 && bullet->y >= map->wall[WallNum].Ry1)
                || (tmp.y >= map->wall[WallNum].Ry1 && bullet->y <= map->wall[WallNum].Ry1 )){
                    bullet->SinDeg *= -1;
                }
            }
        }
    }
    bullet->y += BullStep* bullet->SinDeg ;
    bullet->x += BullStep* bullet->CosDeg ;
}

void TMPMoveBullet (Bullet* bullet){
    bullet->y += BullStep* bullet->SinDeg ;
    bullet->x += BullStep* bullet->CosDeg ;
}
