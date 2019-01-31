
#ifndef MAIN_C_STARTOFGAME_H
#define MAIN_C_STARTOFGAME_H

void StartGame (int NumOfTank , SDL_Renderer* renderer ,  SDL_Window* window);
void DefinitionOfAskPointNumberBox(NumberBox* numberBox);
int AskWinPoint (SDL_Renderer* renderer , Map* map , SDL_Window* window);
void ManageFirstPage (FirstPage* FirstPage , SDL_Renderer* renderer, SDL_Window* window);

#endif //MAIN_C_STARTOFGAME_H
