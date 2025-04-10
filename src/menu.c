#include "../util/include.h"
#include "../util/global.h"
#include "../util/util.h"

void DisplayMenu(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, skytexture, NULL, NULL);
    SDL_RenderCopy(renderer, cloudtexture, NULL, NULL);
    SDL_RenderCopy(renderer, menutexture, NULL, NULL);
}

void HandleMenu(SDL_Event *event)
{

    SDL_Rect playbutton = {610, 300, 730, 400};

    if (event->type == SDL_MOUSEBUTTONDOWN)
    {
        int mouseX = event->button.x;
        int mouseY = event->button.y;

        if (mouseX >= playbutton.x && mouseX <= playbutton.x + playbutton.w &&
            mouseY >= playbutton.y && mouseY <= playbutton.y + playbutton.h)
            currentState = GAME;
    }
}
