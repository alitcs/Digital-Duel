#include "../util/include.h"
#include "../util/global.h"
#include "../util/util.h"

SDL_Renderer *renderer = NULL;
SDL_Window *window = NULL;
SDL_Event event;
GameState currentState = MENU;

SDL_Texture *skytexture = NULL;
SDL_Texture *cloudtexture = NULL;
SDL_Texture *menutexture = NULL;
SDL_Texture *maptexture = NULL;
SDL_Texture *bullettexture = NULL;
SDL_Texture *gameovertexture = NULL;

Player player1 = {{60, 950, 90, 90}, 0.0, 0, 0, {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}, 0, 0, NULL, 1};
Player player2 = {{1775, 55, 90, 90}, 0.0, 0, 0, {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}, 0, 0, NULL, 0};

Player *players[] = {&player1, &player2};

Uint32 currentTime = 0;

int main(void)
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Could Not Initialize Video\nSDL2 Error: %s\n", SDL_GetError());
        return 1;
    }

    if (IMG_Init((IMG_INIT_PNG)&IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        printf("IMG_Init Error\nSDL Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    window = SDL_CreateWindow(
        "Digital Duel",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1920,
        1080,
        SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        printf("Window Could Not Be Created\nSDL Error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        printf("Rendering Error\nSDL Error: %s\n", SDL_GetError());
        CleanUp();
        return 1;
    }

    skytexture = GetImage("assets/images/sky.png");
    cloudtexture = GetImage("assets/images/clouds.png");
    menutexture = GetImage("assets/images/menu.png");
    maptexture = GetImage("assets/images/map.png");
    player1.texture = GetImage("assets/images/redplayer.png");
    player2.texture = GetImage("assets/images/blueplayer.png");
    bullettexture = GetImage("assets/images/bullet.png");
    gameovertexture = GetImage("assets/images/gameover.png");

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    int running = 1;

    Uint32 lastTime = SDL_GetTicks();
    float gameoverdeltaTime = 0.0;

    while (running)
    {
        currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;
            if (currentState == MENU)
                HandleMenu(&event);
        }

        SDL_RenderClear(renderer);

        if (currentState == MENU)
        {
            DisplayMenu(renderer);
        }
        else if (currentState == GAME)
        {
            HandleGame(renderer, &player1, &player2, deltaTime);
            DisplayGame(renderer, &player1, &player2);
        }
        else if (currentState == GAMEOVER)
        {
            DisplayGameOver(renderer);
            gameoverdeltaTime = (SDL_GetTicks() - gameovercurrentTime) / 1000.0f;

            if (gameoverdeltaTime > 3.0)
            {
                gameoverdeltaTime = 0.0;
                ResetGame(renderer, &player1, &player2);
                currentState = MENU;
            }
        }

        SDL_RenderPresent(renderer);
    }

    CleanUp();
    return 0;
}
