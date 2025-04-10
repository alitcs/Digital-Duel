#include "../util/include.h"
#include "../util/global.h"
#include "../util/util.h"

#define PLAYER_SPEED 300
#define SCREEN_HEIGHT 1080
#define SCREEN_WIDTH 1920
#define COOL_DOWN_TIME 400

Uint32 gameovercurrentTime = 0;

typedef struct
{
    SDL_Rect rect;
} Boundary;

Boundary boundaries[18] = {
    {0, -25, SCREEN_WIDTH, 10},
    {-25, 0, 10, SCREEN_HEIGHT},
    {SCREEN_WIDTH, 0, 10, SCREEN_HEIGHT},
    {0, SCREEN_HEIGHT, SCREEN_WIDTH, 10},
    {235, 235, 25, 25},
    {525, 325, 50, 50},
    {635, 225, 130, 40},
    {325, 440, 40, 130},
    {725, 625, 40, 40},
    {635, 825, 130, 40},
    {435, 835, 40, 180},
    {1030, 425, 50, 50},
    {1320, 725, 50, 50},
    {1135, 830, 130, 40},
    {1530, 535, 40, 130},
    {1630, 835, 40, 40},
    {1230, 240, 235, 33},
    {1425, 0, 40, 200}};

void DisplayGame(SDL_Renderer *renderer, Player *player1, Player *player2)
{
    SDL_RenderCopy(renderer, maptexture, NULL, NULL);
    SDL_RenderCopyEx(renderer, player1->texture, NULL, &(player1->rect), player1->angle, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(renderer, player2->texture, NULL, &(player2->rect), player2->angle, NULL, SDL_FLIP_NONE);
    for (int i = 0; i < player1->bulletc; i++)
    {
        if (player1->bullets[i])
        {
            SDL_RenderCopyEx(renderer, bullettexture, NULL, &(player1->bullets[i]->rect), player1->bullets[i]->angle, NULL, SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
        }
    }

    for (int i = 0; i < player2->bulletc; i++)
    {
        if (player2->bullets[i])
        {
            SDL_RenderCopyEx(renderer, bullettexture, NULL, &(player2->bullets[i]->rect), player2->bullets[i]->angle, NULL, SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
        }
    }
}

void DisplayGameOver(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, gameovertexture, NULL, NULL);
}

int CheckCollision(SDL_Rect *rect)
{
    for (int i = 0; i < 18; i++)
    {
        if (SDL_HasIntersection(rect, &boundaries[i].rect))
        {
            return 1;
        }
    }
    return 0;
}

int CheckPlayerCollision(Bullet *bullet, Player *player)
{
    if (SDL_HasIntersection(&(bullet->rect), &(player->rect)))
        return 1;
    return 0;
}

Bullet *ShootBullet(Player *player)
{
    Bullet *bullet = malloc(sizeof(Bullet));
    if (!bullet)
        return NULL;

    bullet->rect.x = player->rect.x + 45;
    bullet->rect.y = player->rect.y + 45;
    bullet->rect.h = 15;
    bullet->rect.w = 15;
    bullet->angle = player->angle;
    bullet->velocityX = cos((player->angle + 90.0) * M_PI / 180.0f) * 1800;
    bullet->velocityY = sin((player->angle + 90.0) * M_PI / 180.0f) * 1800;
    bullet->texture = bullettexture;
    return bullet;
}

void UpdateBullets(Player *player, float deltaTime)
{
    for (int i = 0; i < player->bulletc; i++)
    {
        if (player->bullets[i])
        {

            player->bullets[i]->rect.x += player->bullets[i]->velocityX * deltaTime;
            player->bullets[i]->rect.y += player->bullets[i]->velocityY * deltaTime;

            if (CheckCollision(&(player->bullets[i]->rect)))
            {
                free(player->bullets[i]);
                player->bullets[i] = player->bullets[player->bulletc - 1];
                player->bullets[player->bulletc - 1] = NULL;
                player->bulletc--;
            }
            if (CheckPlayerCollision(player->bullets[i], players[player->index]))
            {
                free(player->bullets[i]);
                player->bullets[i] = player->bullets[player->bulletc - 1];
                player->bullets[player->bulletc - 1] = NULL;
                player->bulletc--;
                currentState = GAMEOVER;
                gameovercurrentTime = SDL_GetTicks();
            }
        }
    }
}

void HandlePlayerInput(Player *player, SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right, SDL_Scancode shoot, const Uint8 *keyState, float deltaTime)
{
    int moveX = 0, moveY = 0;
    Bullet bullet;

    if (keyState[up])
        moveY = -PLAYER_SPEED;
    if (keyState[down])
        moveY = PLAYER_SPEED;
    if (keyState[left])
        moveX = -PLAYER_SPEED;
    if (keyState[right])
        moveX = PLAYER_SPEED;
    if (keyState[shoot] && currentTime - player->lastbuttonpress > COOL_DOWN_TIME)
    {
        if (player->bulletc >= 10)
            return;

        Bullet *bullet = ShootBullet(player);
        if (!bullet)
            return;

        player->bullets[player->bulletc] = bullet;
        player->bulletc++;
        player->lastbuttonpress = currentTime;
    }

    SDL_Rect tempRectX = player->rect;
    SDL_Rect tempRectY = player->rect;

    tempRectX.x += (int)(moveX * deltaTime);
    tempRectY.y += (int)(moveY * deltaTime);

    if (!CheckCollision(&tempRectX))
    {
        player->rect.x = tempRectX.x;
    }

    if (!CheckCollision(&tempRectY))
    {
        player->rect.y = tempRectY.y;
    }

    if (moveX != 0 || moveY != 0)
    {
        float magnitude = sqrt(moveX * moveX + moveY * moveY);
        player->velocityX = (moveX / magnitude) * PLAYER_SPEED;
        player->velocityY = (moveY / magnitude) * PLAYER_SPEED;
        player->angle = atan2(player->velocityY, player->velocityX) * (180.0 / M_PI) - 90.0;
    }
    else
    {
        player->velocityX = 0;
        player->velocityY = 0;
    }
}

void UpdatePlayer(Player *player, float deltaTime)
{
    player->rect.x += (int)(player->velocityX * deltaTime);
    player->rect.y += (int)(player->velocityY * deltaTime);
}

void RenderPlayer(SDL_Renderer *renderer, Player *player)
{
    SDL_RenderCopyEx(renderer, player->texture, NULL, &player->rect, player->angle, NULL, SDL_FLIP_NONE);
}

void ResetGame(SDL_Renderer *renderer, Player *player1, Player *player2)
{
    ResetPlayer(player1, 60, 950, 1);
    ResetPlayer(player2, 1775, 55, 0);
}

void ResetPlayer(Player *player, int startX, int startY, int index)
{
    player->rect.x = startX;
    player->rect.y = startY;
    player->rect.w = 90;
    player->rect.h = 90;
    player->angle = 0.0f;
    player->velocityX = 0;
    player->velocityY = 0;
    player->bulletc = 0;
    player->lastbuttonpress = 0;
    player->index = index;

    for (int i = 0; i < player->bulletc; i++)
    {
        if (player->bullets[i])
        {
            free(player->bullets[i]);
            player->bullets[i] = NULL;
        }
    }
}

void HandleGame(SDL_Renderer *renderer, Player *player1, Player *player2, float deltaTime)
{
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    HandlePlayerInput(player1, SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_E, keyState, deltaTime);
    HandlePlayerInput(player2, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_SLASH, keyState, deltaTime);

    UpdateBullets(player1, deltaTime);
    UpdateBullets(player2, deltaTime);
    RenderPlayer(renderer, player1);
    RenderPlayer(renderer, player2);
}
