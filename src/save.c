
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "save.h"
#include "struct.h"
#include "startofgame.h"
#include "newround.h"

void SaveGame (Map* map){
    FILE* fp;
    char address [20] = "../Saves/1.txt";
    fp = fopen(address, "w");
    fprintf(fp , "%d %d %d\n" , map->NumOfTanks  , map->NumOfWalls , map->WinPoint);
    for (int i=0; i<map->NumOfWalls; i++)
        fprintf(fp ,"%d %d %d %d\n" , map->wall[i].x1, map->wall[i].y1, map->wall[i].x2, map->wall[i].y2);
    for (int i=0; i<map->NumOfTanks; i++) {
        fprintf(fp, "%lf %lf %lf\n", map->tank[i].x, map->tank[i].y, map->tank[i].deg);
        fprintf(fp, "%d %d %d %d\n", map->tank[i].NumOFExitBulls , map->tank[i].Score , map->tank[i].TimeOfLoss , map->tank[i].IsAlive);
        for (int j=0; j<NumOfBulls; j++) {
            fprintf(fp ,"%d %d %lf %lf %lf %lf\n", map->tank[i].bullet[j].Exist , map->tank[i].bullet[j].TimeAppear ,
                                               map->tank[i].bullet[j].x ,     map->tank[i].bullet[j].y ,
                                               map->tank[i].bullet[j].CosDeg ,map->tank[i].bullet[j].SinDeg);
        }
    }
    fprintf(fp , "%d %d %d %d %d\n" , map->IsAlive , map->WinnerTank, map->DeathTime, map->GameTime ,map->frames);
    fclose(fp);
}

void LoadGame (SDL_Renderer* renderer ,SDL_Window* window){
    Map map;
    map.Enabled = 1;
    map.WinnerTank = -1;
    FILE* fp;
    char address [20] = "../Saves/1.txt";
    fp = fopen(address, "r");
    fscanf(fp , "%d %d %d\n" , &map.NumOfTanks  , &map.NumOfWalls , &map.WinPoint);
    Definition(&map);
    for (int i=0; i<map.NumOfWalls; i++){
        fscanf(fp ,"%d %d %d %d\n" , &map.wall[i].x1, &map.wall[i].y1, &map.wall[i].x2, &map.wall[i].y2);
        if (i + 1 == map.NumOfWalls){
            map.x = map.wall[i].x2;
            map.y = map.wall[i].y2;
        }
        map.wall[i].exist = 1;
        map.wall[i].Color.a = 255;
        map.wall[i].Color.r = 0;
        map.wall[i].Color.g = 0;
        map.wall[i].Color.b = 0;
    }
    for (int i=0; i<map.NumOfWalls; i++){
        map.wall[i].Rx1 = 25.0 + 950.0 * map.wall[i].x1 / map.x;
        map.wall[i].Rx2 = 25.0 + 950.0 * map.wall[i].x2 / map.x;
        map.wall[i].Ry1 = 25.0 + 950.0 * map.wall[i].y1 / map.y;
        map.wall[i].Ry2 = 25.0 + 950.0 * map.wall[i].y2 / map.y;
    }
    for (int i=0; i<map.NumOfTanks; i++) {
        fscanf(fp, "%lf %lf %lf\n", &map.tank[i].x, &map.tank[i].y, &map.tank[i].deg);
        fscanf(fp, "%d %d %d %d\n", &map.tank[i].NumOFExitBulls , &map.tank[i].Score , &map.tank[i].TimeOfLoss , &map.tank[i].IsAlive);
        for (int j=0; j<NumOfBulls; j++) {
            fscanf(fp ,"%d %d %lf %lf %lf %lf\n", &map.tank[i].bullet[j].Exist , &map.tank[i].bullet[j].TimeAppear ,
                    &map.tank[i].bullet[j].x ,    &map.tank[i].bullet[j].y ,
                    &map.tank[i].bullet[j].CosDeg ,&map.tank[i].bullet[j].SinDeg);
        }
    }
    fscanf(fp , "%d %d %d %d %d\n" , &map.IsAlive , &map.WinnerTank, &map.DeathTime, &map.GameTime ,&map.frames);
    fclose(fp);
    map.Enabled = 1;
    ManageRound(&map , renderer, window);
}