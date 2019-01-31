
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "save.h"
#include "struct.h"

void SaveGame (Map* map){
    FILE* fp;
    char address [20] = "./Saves/1.txt";
    fp = fopen(address, "w");
    fprintf(fp , "df");
    fclose(fp);
}