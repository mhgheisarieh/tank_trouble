#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <time.h>
#include "maps.h"
#include "view.h"


void LoadMap (Map* map){
    FILE *fp;
    char filename [10] = "maps\\" ;
    srand(time(NULL));
    int k = rand() % 3;
    filename [5]= '0' + k + 1;
    for (int i=6; i<10; i++){
        filename[i] = 0;
    }
    strcat (filename , ".txt");
    fp = fopen(filename, "r");
    fscanf(fp, "%d\n", &map->NumOfWalls);
    for (int i=0; i<map->NumOfWalls; i++){
        fscanf(fp, "%d %d %d %d\n", &map->wall[i].x1, &map->wall[i].y1 , &map->wall[i].x2 , &map->wall[i].y2);
        if (i + 1 == map->NumOfWalls){
            map->x = map->wall[i].x2;
            map->y = map->wall[i].y2;
        }
        map->wall[i].exist = 1;
        map->wall[i].Color.a = 255;
        map->wall[i].Color.r = 0;
        map->wall[i].Color.g = 0;
        map->wall[i].Color.b = 0;
    }
    fclose(fp);
    for (int i=0; i<map->NumOfWalls; i++){
        map->wall[i].Rx1 = 25.0 + 750.0 * map->wall[i].x1 / map->x;
        map->wall[i].Rx2 = 25.0 + 750.0 * map->wall[i].x2 / map->x;
        map->wall[i].Ry1 = 25.0 + 750.0 * map->wall[i].y1 / map->y;
        map->wall[i].Ry2 = 25.0 + 750.0 * map->wall[i].y2 / map->y;
    }
}
