/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:08:25 by hhismans          #+#    #+#             */
/*   Updated: 2016/08/07 17:52:47 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXEL_H
# define PIXEL_H
#include <SDL.h>

#define BLACK 0
#define WHITE 1
#define CHIP8WIDTH 64
#define CHIP8HEIGHT 32
#define PIXSIZE 8
#define WIDTH CHIP8WIDTH * PIXSIZE
#define HEIGHT CHIP8HEIGHT * PIXSIZE

typedef struct	s_pixel
{
	SDL_Rect	position; // x, y, w(width), h (height)
	Uint8		color; // bool can do stuff here, just black and white;
}				t_pixel;

SDL_Surface	*screen, *carre[2];
t_pixel		pixel[CHIP8WIDTH][CHIP8HEIGHT];

SDL_Event event;

void initPixel();
void initScreen();
void drawPixel(t_pixel pixel);
void cleanScreen();
void updateScreen();

#endif

