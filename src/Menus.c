#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Menus.h"
#include "struct.h"

void DefinitionOfMainMenu (FirstPage* FirstPage){

    FirstPage->buttons[0].y1= 100;
    FirstPage->buttons[0].y2= 225;
    FirstPage->buttons[0].action = Play3v3;
    sprintf (FirstPage->buttons[0].text ,"New 3v3 Game!");

    FirstPage->buttons[1].y1 = 275;
    FirstPage->buttons[1].y2 = 400;
    FirstPage->buttons[1].action = Play2v2;
    sprintf (FirstPage->buttons[1].text ,"New 2v2 Game!");

    FirstPage->buttons[2].y1 = 450;
    FirstPage->buttons[2].y2 = 575;
    FirstPage->buttons[2].action = load;
    sprintf (FirstPage->buttons[2].text ,"Load Game");

    FirstPage->buttons[3].y1 = 625;
    FirstPage->buttons[3].y2 = 750;
    FirstPage->buttons[3].action = about;
    sprintf (FirstPage->buttons[3].text ,"About Game");

    FirstPage->buttons[4].y1 = 800;
    FirstPage->buttons[4].y2 = 925;
    FirstPage->buttons[4].action = quit;
    sprintf (FirstPage->buttons[4].text ,"Quit");

    FirstPage->ButtonColor.b = 100;
    FirstPage->ButtonColor.g = 100;
    FirstPage->ButtonColor.r =  250;
    FirstPage->ButtonColor.a =  200;
    FirstPage->SelectedColor.b = 250;
    FirstPage->SelectedColor.g = 100;
    FirstPage->SelectedColor.r =  100;
    FirstPage->SelectedColor.a =  200;
    FirstPage->SelectedButtonNum = 0;
    FirstPage->Action = None;

}

void DefinitionOfMiddleMenu (MiddlePage* MiddlePage){

    MiddlePage->buttons[0].y1 = 275;
    MiddlePage->buttons[0].y2 = 400;
    MiddlePage->buttons[0].action = resume;
    sprintf (MiddlePage->buttons[0].text , "Resume (ESC)");

    MiddlePage->buttons[1].y1 = 450;
    MiddlePage->buttons[1].y2 = 575;
    MiddlePage->buttons[1].action = save;
    sprintf (MiddlePage->buttons[1].text , "Save Game (S)");

    MiddlePage->buttons[2].y1 = 625;
    MiddlePage->buttons[2].y2 = 750;
    MiddlePage->buttons[2].action = Back;
    sprintf (MiddlePage->buttons[2].text , "Skip Game (Backspace)");

    MiddlePage->Action = None;
    MiddlePage->SelectedColor.r = 100;
    MiddlePage->SelectedColor.g = 100;
    MiddlePage->SelectedColor.b = 250;
    MiddlePage->SelectedColor.a = 200;
    MiddlePage->ButtonColor.r = 250;
    MiddlePage->ButtonColor.g = 100;
    MiddlePage->ButtonColor.b = 100;
    MiddlePage->ButtonColor.a = 200;
    MiddlePage->BackgroundColor.r = 250;
    MiddlePage->BackgroundColor.g = 225;
    MiddlePage->BackgroundColor.b = 200;
    MiddlePage->BackgroundColor.a = 150;
    MiddlePage->SelectedButtonNum = 0;
}

//
//    FirstPage->buttons[4].y = 460;
//    FirstPage->buttons[4].x1 = 20;
//    FirstPage->buttons[4].x2 = 380;
//    FirstPage->buttons[4].action = setting;
//    FirstPage->buttons[4].ActionKey = SDLK_p;
//    sprintf (FirstPage->buttons[4].text ,"Preference");