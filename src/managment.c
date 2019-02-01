#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "struct.h"
#include "newround.h"
#include "startofgame.h"
#include "Menus.h"

void LossOfTank (Tank* tank , Bullet* bullet){
    bullet->Exist = 0;
    tank->IsAlive = 0;
}

void LossOfTankWithMine (Tank* tank , Mine* mine){
    mine->Enabled = 0;
    tank->IsAlive = 0;
}

void FadeTank (Tank* tank ){
    if (tank->BodyColor.a <= 5 && tank->InnerColor.a<= 5 && tank->PipeColor.a<= 5){
        tank->FullDied =1;
        return;
    }
    tank->BodyColor.a -=3;
    tank->InnerColor.a -=3;
    tank->PipeColor.a -=3;
}

void CheckBullets (Map* map){
    for (int i=0; i<map->NumOfTanks ; i++){
        for (int j=0; j<map->NumOfTanks ; j++){
            for (int k=0; k<NumOfBulls; k++){
                double distance = sqrt ((map->tank[i].x - map->tank[j].bullet[k].x) * (map->tank[i].x - map->tank[j].bullet[k].x)
                                        + (map->tank[i].y - map->tank[j].bullet[k].y) * (map->tank[i].y - map->tank[j].bullet[k].y));
                if (distance <= TankRadius && map->tank[i].IsAlive &&  map->tank[j].bullet[k].Exist) {
                    LossOfTank(&map->tank[i] , &map->tank[j].bullet[k]);
                    map->tank[j].NumOFExitBulls --;
                }
            }
        }
    }
}

void CheckMines (Map* map){
    for (int i=0; i<map->NumOfTanks ; i++){
        for (int j=0; j<map->NumOfTanks ; j++){
            for (int k=0; k<10; k++){
                double distance = sqrt ((map->tank[i].x - map->tank[j].mine[k].x) * (map->tank[i].x - map->tank[j].mine[k].x)
                                        + (map->tank[i].y - map->tank[j].mine[k].y) * (map->tank[i].y - map->tank[j].mine[k].y));
                if (distance <= TankRadius * 2 && map->tank[i].IsAlive &&
                map->tank[j].mine[k].Enabled && map->frames - map->tank[j].mine[k].TimeOfMining > 2 * Second) {
                    LossOfTankWithMine(&map->tank[i] , &map->tank[j].mine[k]);
                    map->tank[j].mine[k].ExploseTime = map->frames;
                    map->tank[j].mine[k].IsExplosed = 1;
                }
            }
        }
    }
}

void CheckGame(Map* map){
    CheckBullets(map);
    CheckMines (map);
    int NumOfAliveTanks = 0;
    for (int i=0; i<map->NumOfTanks; i++){
        if (map->tank[i].IsAlive) NumOfAliveTanks++;
        if (!map->tank[i].IsAlive && map->Enabled) FadeTank (&map->tank[i]);
    }
    if (map->IsAlive && NumOfAliveTanks == 1){
        map->IsAlive = 0;
        map->DeathTime = map->GameTime;
    }
    if (map->GameTime - map->DeathTime > TimeOfBetweenGames && !map->IsAlive){
        for (int i=0; i<map->NumOfTanks; i++){
            if (map->tank[i].IsAlive)
                 map->tank[i].Score ++;
        }
        bool IsEndedGame = 0;
        for (int i=0; i<map->NumOfTanks; i++){
            if (map->tank[i].Score == map->WinPoint){
                IsEndedGame = 1;
                map->Enabled = 0;
                map->WinnerTank = i;
            }
        }
        if(!IsEndedGame)
            NewRound(map);
    }
}