/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 18:26:51 by hhismans          #+#    #+#             */
/*   Updated: 2016/08/07 20:21:58 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "cpu.h"
#include "pixel.h"

void initSDL();
void quitSDL();
void pause();

int main()
{
	int keepGoing = 1;

	initSDL();
	initScreen();
	initPixel();

	while (keepGoing)
	{
		updateScreen();
		SDL_Delay(FPS);
	}
	pause(); //last pause before finish
	return (0);
}

void initSDL()
{
	atexit(quitSDL);
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		fprintf(stderr, "error init SDL %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void quitSDL()
{
	SDL_FreeSurface(carre[0]);
	SDL_FreeSurface(carre[1]);
	SDL_Quit();
}
void pause()
{
	int keepGoing = 1;
	while(keepGoing)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				keepGoing = 0;
				break;
			case SDL_KEYDOWN:
				keepGoing = 0;
				break;
			default:
				break;
		}
	}
}
