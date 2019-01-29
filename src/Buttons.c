#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Buttons.h"
#include "struct.h"

void DefinitionOfButtons (FirstPage* FirstPage){

    FirstPage->buttons[0].y= 60;
    FirstPage->buttons[0].x1 = 20;
    FirstPage->buttons[0].x2 = 380;
    FirstPage->buttons[0].action = Play3v3;
    FirstPage->buttons[0].ActionKey = SDLK_3;
    sprintf (FirstPage->buttons[0].text ,"Play 3v3");

    FirstPage->buttons[1].y = 160;
    FirstPage->buttons[1].x1 = 20;
    FirstPage->buttons[1].x2 = 380;
    FirstPage->buttons[1].action = Play2v2;
    FirstPage->buttons[1].ActionKey = SDLK_2;
    sprintf (FirstPage->buttons[1].text ,"Play 2v2");

    FirstPage->buttons[2].y = 260;
    FirstPage->buttons[2].x1 = 20;
    FirstPage->buttons[2].x2 = 380;
    FirstPage->buttons[2].action = load;
    FirstPage->buttons[2].ActionKey = SDLK_l;
    sprintf (FirstPage->buttons[2].text ,"Load Game");

    FirstPage->buttons[3].y = 360;
    FirstPage->buttons[3].x1 = 20;
    FirstPage->buttons[3].x2 = 380;
    FirstPage->buttons[3].action = save;
    FirstPage->buttons[3].ActionKey = SDLK_s;
    sprintf (FirstPage->buttons[3].text ,"Save Game");

    FirstPage->buttons[4].y = 460;
    FirstPage->buttons[4].x1 = 20;
    FirstPage->buttons[4].x2 = 380;
    FirstPage->buttons[4].action = setting;
    FirstPage->buttons[4].ActionKey = SDLK_p;
    sprintf (FirstPage->buttons[4].text ,"Preference");

    FirstPage->buttons[5].y = 560;
    FirstPage->buttons[5].x1 = 20;
    FirstPage->buttons[5].x2 = 380;
    FirstPage->buttons[5].action = about;
    FirstPage->buttons[5].ActionKey = SDLK_F1;
    sprintf (FirstPage->buttons[5].text ,"About Game");

    FirstPage->buttons[6].y = 660;
    FirstPage->buttons[6].x1 = 20;
    FirstPage->buttons[6].x2 = 380;
    FirstPage->buttons[6].action = quit;
    FirstPage->buttons[6].ActionKey = SDLK_q;
    sprintf (FirstPage->buttons[6].text ,"Quit");

    FirstPage->ButtonColor.b = FirstPage->ButtonColor.g = FirstPage->ButtonColor.r =  200;
    FirstPage->SelectedColor.b = FirstPage->SelectedColor.g = FirstPage->SelectedColor.r =  100;
    FirstPage->SelectedButtonNum = 0;
    FirstPage->Action = None;

}