
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "events.h"
#include "struct.h"
#include "physics.h"

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
            return Exit;
    }
}
