#include "include.h"
#include "global.h"
#include "util.h"
void CleanUp()
{
	if (renderer)
		SDL_DestroyRenderer(renderer);
	if (window)
		SDL_DestroyWindow(window);
	if (player1.texture)
		SDL_DestroyTexture(player1.texture);
	if (player2.texture)
		SDL_DestroyTexture(player2.texture);
	if (skytexture)
		SDL_DestroyTexture(skytexture);
	if (maptexture)
		SDL_DestroyTexture(maptexture);
	if (cloudtexture)
		SDL_DestroyTexture(cloudtexture);
	if (menutexture)
		SDL_DestroyTexture(menutexture);
	if (bullettexture)
		SDL_DestroyTexture(bullettexture);
	if (gameovertexture)
		SDL_DestroyTexture(gameovertexture);
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture *GetImage(char *str)
{
	SDL_Surface *surface = IMG_Load(str);
	if (!surface)
	{
		printf("IMG_Load Error\nSDL Error: %s\n", IMG_GetError());
		CleanUp();
		exit(1);
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
	{
		printf("SDL_CreateTextureFromSurface Error\nSDL Error: %s\n", SDL_GetError());
		CleanUp();
		exit(1);
	}
	return texture;
}

void render_new_screen(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}
