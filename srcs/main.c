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

    SDL_Surface *ecran = NULL;
    
    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
	if (ecran == NULL)
	{
		printf("ecran null\n");
	}
    SDL_WM_SetCaption("Ma super fenêtre SDL !", NULL);
    
    // Coloration de la surface ecran en bleu-vert
    if (SDL_FillRect(ecran, NULL, 0))
	{
		printf("error on SDL_FillRect() %s\n", SDL_GetError());
		exit(-1);
	}

    if (SDL_Flip(ecran) == -1)
	{
		printf("error on SDL_FLIP() %s\n", SDL_GetError());
		exit(-1);
	}
	else
	{
		printf("flip succes\n");
	}

 /* Mise à jour de l'écran avec sa nouvelle couleur */	
/*
	initSDL();
	initScreen();
	initPixel();
	cleanScreen();
	updateScreen();*/
	pause();
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
