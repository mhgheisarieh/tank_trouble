
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "events.h"
#include "struct.h"
#include "physics.h"
#include "startofgame.h"

int handleEvents(Map* map) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        for (int i=0; i<map->NumOfTanks; i++){
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

void handleEventsOfFirstMenu (FirstPage* FirstPage){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_KEYUP){
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    if (FirstPage->SelectedButtonNum == 0) FirstPage->SelectedButtonNum = 7;
                    FirstPage->SelectedButtonNum --;
                    break;
                case SDLK_DOWN:
                    if (FirstPage->SelectedButtonNum == 6) FirstPage->SelectedButtonNum = -1;
                    FirstPage->SelectedButtonNum ++;
                    break;
                case SDLK_RETURN:
                    if (FirstPage->buttons[FirstPage->SelectedButtonNum].action == about ||
                        FirstPage->buttons[FirstPage->SelectedButtonNum].action == save ||
                        FirstPage->buttons[FirstPage->SelectedButtonNum].action == load ||
                        FirstPage->buttons[FirstPage->SelectedButtonNum].action == setting)
                        break;
                    FirstPage->Action = FirstPage->buttons[FirstPage->SelectedButtonNum].action;
                    break;
                case SDLK_2:
                    FirstPage->Action = Play2v2;
                    break;
                case SDLK_3:
                    FirstPage->Action = Play3v3;
                    break;
                case SDLK_F1:
                    //FirstPage->Action = about;
                    break;
                case SDLK_q:
                    FirstPage->Action = quit;
                    break;
                case SDLK_s:
                   // FirstPage->Action = save;
                    break;
                case SDLK_l:
                    //FirstPage->Action = load;
                    break;
                case SDLK_p:
                    //FirstPage->Action = setting;
                    break;
            }
        }
        if (event.window.event==SDL_WINDOWEVENT_CLOSE || FirstPage->Action == quit)
            FirstPage->Action = quit;
    }
}

void DoAction (enum Actions Action){
    switch (Action){
        case Play2v2:
            StartGame(2);
            break;
        case Play3v3:
            StartGame(3);
            break;
        case quit:
            return;
    }
}