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
    tank->PipeColor.r = 255;
    tank->PipeColor.g = 255;
    tank->PipeColor.b = 255;
    tank->PipeColor.a = 255;
    tank->BodyColor.r = 255;
    tank->BodyColor.g = 255;
    tank->BodyColor.b = 255;
    tank->BodyColor.a = 255;
    tank->InnerColor.r = 255;
    tank->InnerColor.g = 255;
    tank->InnerColor.b = 255;
    tank->InnerColor.a = 255;
}

void CheckBullets (Map* map){
    for (int i=0; i<map->NumOfTanks ; i++){
        for (int j=0; j<map->NumOfTanks ; j++){
            for (int k=0; k<NumOfBulls; k++){
                double distance = sqrt ((map->tank[i].x - map->tank[j].bullet[k].x) * (map->tank[i].x - map->tank[j].bullet[k].x)
                                        + (map->tank[i].y - map->tank[j].bullet[k].y) * (map->tank[i].y - map->tank[j].bullet[k].y));
                if (distance <= TankRadius && map->tank[i].IsAlive &&  map->tank[j].bullet[k].Exist) {
                    LossOfTank(&map->tank[i] , &map->tank[j].bullet[k]);
                }
            }
        }
    }
}

void CheckGame(Map* map){
    CheckBullets(map);
    int NumOfAliveTanks = 0;
    for (int i=0; i<map->NumOfTanks; i++){
        if (map->tank[i].IsAlive) NumOfAliveTanks++;
    }
    if (map->IsAlive && NumOfAliveTanks == 1){
        map->IsAlive = 0;
        map->DeathTime = SDL_GetTicks()-map->StartRoundTime;
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
                map->WinnerTank = &map->tank[i];
            }
        }
        if(!IsEndedGame)
            NewRound(map);
    }
}