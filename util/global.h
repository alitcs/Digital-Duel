#include <SDL2/SDL.h>
#ifndef GLOBAL_H
#define GLOBAL_H

typedef enum
{
        MENU,
        GAME,
        GAMEOVER
} GameState;

typedef struct
{
        SDL_Rect rect;
        float angle;
        float velocityX;
        float velocityY;
        SDL_Texture *texture;
} Bullet;

typedef struct
{
        SDL_Rect rect;
        float angle;
        float velocityX;
        float velocityY;
        Bullet *bullets[10];
        int bulletc;
        Uint32 lastbuttonpress;
        SDL_Texture *texture;
        int index;
} Player;
extern Player *players[];
extern Uint32 currentTime;
extern SDL_Texture *bullettexture;
extern SDL_Texture *skytexture;
extern SDL_Texture *cloudtexture;
extern SDL_Texture *menutexture;
extern SDL_Texture *maptexture;
extern SDL_Texture *gameovertexture;
extern Player player1;
extern Player player2;
extern GameState currentState;
extern SDL_Renderer *renderer;
extern SDL_Window *window;
extern SDL_Event event;
extern GameState currentState;
extern Uint32 gameovercurrentTime;
#endif
