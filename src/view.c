#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "view.h"
#include "physics.h"
#include "logic.h"

int handleEvents(Map* map) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        for (int i=0; i<NumOfTank; i++){
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == map->tank[i].Down_key)
                    map->tank[i].Key.Down_key = 1;
                if (event.key.keysym.sym == map->tank[i].Up_key)
                    map->tank[i].Key.Up_key = 1;
                if (event.key.keysym.sym == map->tank[i].Left_Key)
                    map->tank[i].Key.Left_Key = 1;
                if (event.key.keysym.sym == map->tank[i].Right_Key)
                    map->tank[i].Key.Right_Key = 1;
                if (event.key.keysym.sym == map->tank[i].Shoot_Key && map->tank[i].canshoot) {
                    fire(&(map->tank[i]));
                    map->tank[i].canshoot = false;
                }
            }
            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == map->tank[i].Down_key)
                    map->tank[i].Key.Down_key = 0;
                if (event.key.keysym.sym == map->tank[i].Up_key) {
                    map->tank[i].Key.Up_key = 0;
                }
                if (event.key.keysym.sym == map->tank[i].Left_Key) {
                    map->tank[i].Key.Left_Key = 0;
                }
                if (event.key.keysym.sym == map->tank[i].Right_Key) {
                    map->tank[i].Key.Right_Key = 0;
                }
                if (event.key.keysym.sym == map->tank[i].Shoot_Key) {
                    map->tank[i].canshoot = true;
                }
            }
        }
        if (event.window.event==SDL_WINDOWEVENT_CLOSE)
            return 12345;
    }
    for (int i=0; i<NumOfTank; i++){
        //IsWall(&map);
        for (int j=0; j<NumOfBulls; j++)
            if (map->tank[i].bullet[j].Exist)
                move_bullet(&map->tank[i].bullet[j]);
    }
}

void DrawMap (Map* map){

}

void DrawTanks (SDL_Renderer* renderer , Tank* tank) {
    for (int i = 0; i < NumOfTank; i++) {
        filledCircleRGBA(renderer, (tank+i)->x, (tank+i)->y, (tank+i)->radius, (tank+i)->Color.r, (tank+i)->Color.g, (tank+i)->Color.b, (tank+i)->Color.a);
        filledCircleRGBA(renderer, (tank+i)->x, (tank+i)->y, (tank+i)->radius / 1.5, 0, 0, 0, 200);
        filledCircleRGBA(renderer, (tank+i)->x, (tank+i)->y, (tank+i)->radius / 4, (tank+i)->Color.r, (tank+i)->Color.g, (tank+i)->Color.b, (tank+i)->Color.a);
        thickLineRGBA(renderer, (tank+i)->x, (tank+i)->y, (tank+i)->x + (20 * cosf((tank+i)->deg)), (tank+i)->y +(20 * sinf((tank+i)->deg)), (tank+i)->radius / 4, (tank+i)->Color.r, (tank+i)->Color.g, (tank+i)->Color.b, (tank+i)->Color.a);
    }
}

void DrawWalls (SDL_Renderer* renderer, Wall* wall){
    int i =0;
    while ((wall+i)->exist == 1){
        thickLineRGBA(renderer, (wall+i)->Rx1 , (wall+i)->Ry1 , (wall+i)->Rx2 , (wall+i)->Ry2 , 3 , wall->Color.r , wall->Color.g , wall->Color.b , wall->Color.a);
        i++;
    }
}

void DrawBullets (SDL_Renderer* renderer, Tank tank[]){
    for (int i = 0; i < NumOfTank; i++)
        for (int j = 0; j < NumOfBulls; j++)
            if((tank + i)->bullet[j].Exist){
                DrawBullet(renderer, &((tank+i)->bullet[j]));
                if (!IsAliveBullet (&((tank+i)->bullet[j]))){
                    (tank+i)->NumOFExitBulls --;
                }
            }
}

void DrawBullet (SDL_Renderer* renderer, Bullet* bullet){
    filledCircleRGBA(renderer, bullet->x, bullet->y, 3, 0, 0, 0, 255);
}

void Quit (SDL_Renderer* renderer ,  SDL_Window* window){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool IsAliveBullet (Bullet* bullet){
    if ((SDL_GetTicks()-(bullet->TimeAppear))>TimeOfBull) {
        bullet->Exist = 0;
        return 0;
    }
    return 1;
}
