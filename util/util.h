#include "include.h"
#ifndef UTIL_H
#define UTIL_H

void CleanUp();
SDL_Texture *GetImage(char *str);
void DisplayMenu(SDL_Renderer *renderer);
void DisplayGame(SDL_Renderer *renderer, Player *player1, Player *player2);
void HandleMenu(SDL_Event *event);
void HandleGame(SDL_Renderer *renderer, Player *player1, Player *player2, float deltaTime);
void DisplayGameOver(SDL_Renderer *renderer);
void ResetGame(SDL_Renderer *renderer, Player *player1, Player *player2);
void ResetPlayer(Player *player, int startX, int startY, int index);
#endif
