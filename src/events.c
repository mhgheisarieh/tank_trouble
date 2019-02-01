
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
#include "save.h"

int handleEvents(Map* map , MiddlePage* MiddlePage ) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (map->Enabled){
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
                        fire(&(map->tank[i]) , map->GameTime);
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
                    if (event.key.keysym.sym == SDLK_ESCAPE){
                        map->Enabled = 0;
                    }
                }
            }
        } else {
            if (event.type == SDL_KEYUP && map->WinnerTank == -1) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        if (MiddlePage->SelectedButtonNum == 0) MiddlePage->SelectedButtonNum = NumOfMiddleMenuButtons;
                        MiddlePage -> SelectedButtonNum --;
                        break;
                    case SDLK_DOWN:
                        if (MiddlePage->SelectedButtonNum == NumOfMiddleMenuButtons -1) MiddlePage->SelectedButtonNum = -1;
                        MiddlePage->SelectedButtonNum ++;
                        break;
                    case SDLK_RETURN:
                        MiddlePage->Action = MiddlePage ->buttons[MiddlePage->SelectedButtonNum].action;
                        break;
                    case SDLK_ESCAPE:
                        MiddlePage->Action = resume;
                        break;
                    case SDLK_BACKSPACE:
                        MiddlePage->Action = Back;
                        break;
                    case SDLK_s:
                        MiddlePage->Action = save;
                        break;
                }
                switch (MiddlePage->Action){
                    case resume:
                        map->Enabled = 1;
                        MiddlePage->Action =None;
                        break;
                    case Back:
                        return ENDGAME;
                    case save:
                        MiddlePage->SelectedButtonNum = 0;
                        map->Enabled = 1;
                        MiddlePage->Action =None;
                        SaveGame (map);
                        break;
                }
            } else if (event.type == SDL_KEYUP && map->WinnerTank != -1 && event.key.keysym.sym == SDLK_RETURN) {
                return ENDGAME;
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
                    if (FirstPage->SelectedButtonNum == 0) FirstPage->SelectedButtonNum = NumOfMainMenuButtons ;
                    FirstPage->SelectedButtonNum --;
                    break;
                case SDLK_DOWN:
                    if (FirstPage->SelectedButtonNum == NumOfMainMenuButtons - 1) FirstPage->SelectedButtonNum = -1;
                    FirstPage->SelectedButtonNum ++;
                    break;
                case SDLK_RETURN:
                    if (FirstPage->buttons[FirstPage->SelectedButtonNum].action == about ||
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
                case SDLK_l:
                    FirstPage->Action = load;
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

int handleEventsOfNumberBox (NumberBox* numberBox){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    if (numberBox->number<1000)
                    numberBox->number ++;
                    break;
                case SDLK_DOWN:
                    if (numberBox->number != 0)
                        numberBox->number --;
                    break;
                case SDLK_RETURN:
                    if (numberBox->number != 0)
                    return ENTER;
                case SDLK_0:
                    if (numberBox->number<100)
                    numberBox->number *= 10;
                    break;
                case SDLK_1:
                    if (numberBox->number<100) {
                        numberBox->number *= 10;
                        numberBox->number += 1;
                    }
                    break;
                case SDLK_2:
                    if (numberBox->number<100) {
                        numberBox->number *= 10;
                        numberBox->number += 2;
                    }
                    break;
                case SDLK_3:
                    if (numberBox->number<100) {
                        numberBox->number *= 10;
                        numberBox->number += 3;
                    }
                    break;
                case SDLK_4:
                    if (numberBox->number<100) {
                        numberBox->number *= 10;
                        numberBox->number += 4;
                    }
                    break;
                case SDLK_5:
                    if (numberBox->number<100) {
                        numberBox->number *= 10;
                        numberBox->number += 5;
                    }
                    break;
                case SDLK_6:
                    if (numberBox->number<100) {
                        numberBox->number *= 10;
                        numberBox->number += 6;
                    }
                    break;
                case SDLK_7:
                    if (numberBox->number<100) {
                        numberBox->number *= 10;
                        numberBox->number += 7;
                    }
                    break;
                case SDLK_8:
                    if (numberBox->number<100) {
                        numberBox->number *= 10;
                        numberBox->number += 8;
                    }
                    break;
                case SDLK_9:
                    if (numberBox->number<100) {
                        numberBox->number *= 10;
                        numberBox->number += 9;
                    }
                    break;
                case SDLK_BACKSPACE:
                    if (numberBox->number>= 10)
                        numberBox->number /= 10;
                    else
                        numberBox->number = 0;
                    break;
            }
        }
        if (event.window.event==SDL_WINDOWEVENT_CLOSE )
            return Exit;
    }
}
