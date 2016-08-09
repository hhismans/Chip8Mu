/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:18:02 by hhismans          #+#    #+#             */
/*   Updated: 2016/08/07 19:18:51 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixel.h"

void initPixel()
{
	for (int x = 0; x < CHIP8WIDTH; x++)
	{
		for (int y = 0; y < CHIP8HEIGHT; y++)
		{
			pixel[x][y].position.x = x * PIXSIZE;
			pixel[x][y].position.y = y * PIXSIZE;
			pixel[x][y].color = BLACK;
		}
	}
}

void initScreen()
{
	screen = NULL;
	carre[0] = NULL;
	carre[1] = NULL;

	screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("Chip8Mu, training for GBmu", NULL);

	if (screen == NULL)
	{
		fprintf(stderr, "error on loarding video mode %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	carre[0] = SDL_CreateRGBSurface(SDL_HWSURFACE, PIXSIZE, PIXSIZE, 32, 0,0,0,0); // define carre noir
	if (carre[0] == NULL)
	{
		fprintf(stderr, "ohhhhhh :( carre casse %s\n ", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FillRect(carre[0], NULL, SDL_MapRGB(carre[0]->format, 0x00, 0x00, 0x00));

	carre[1]=SDL_CreateRGBSurface(SDL_HWSURFACE,PIXSIZE,PIXSIZE,32,0,0,0,0);
	if(carre[1]==NULL)
	{
		fprintf(stderr,"Erreur lors du chargement de la surface %s",SDL_GetError()); 
		exit(EXIT_FAILURE); 
	}
	SDL_FillRect(carre[1],NULL,SDL_MapRGB(carre[1]->format,0xFF,0xFF,0xFF));
}

void drawPixel(t_pixel pixel)
{
	SDL_BlitSurface(carre[pixel.color], NULL, screen, &pixel.position);
}

void cleanScreen()
{
	for (int x = 0; x < CHIP8WIDTH; x++)
	{
		for (int y = 0; y < CHIP8HEIGHT; y++)
		{
			pixel[x][y].color = BLACK;
		}
	}
	SDL_FillRect(screen, NULL, BLACK);
}

void updateScreen()
{
	char tab[64][32];
	for (int x = 0; x < CHIP8WIDTH; x++)
	{
		for (int y = 0; y < CHIP8HEIGHT; y++)
		{
			drawPixel(pixel[x][y]);
		}
	}
	SDL_Flip(screen);
}
