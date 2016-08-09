/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 16:38:13 by hhismans          #+#    #+#             */
/*   Updated: 2016/08/07 18:40:20 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_H
# define CPU_H
#include <SDL.h>

#define GAMENAME	"C8PIC.ch8"
#define MEMORYSIZE	4096
#define NREGISTER	16
#define STARTADRESS 0x200
#define CPUSPEED	4
#define FPS			16//ms delay 60Hz (1/60)

/*************
 * CPU
 * ***********/
typedef struct	s_cpu
{
	Uint8	memory[MEMORYSIZE]; // size of memory
	Uint16	I; //A que on est ou ?
	Uint16	pc; // program counter Uint16 -> will be between 0 and 4096 * 8
	Uint8	V[NREGISTER]; // registre Chip8 (0xF registre)
	Uint16	jump[16]; // stack, contian adress
	Uint8	jumpCounter; // count nbr of jump
	Uint8	gameCounter; // synchro, 60 Hz
	Uint8	soundCounter;

}				t_cpu;

#define NBROPCODE 35
typedef struct	s_opcode
{
	Uint16 masque[NBROPCODE];
	Uint16 id[NBROPCODE];
}				t_opcode;



t_cpu		cpu;
t_opcode	opc;
void		initCpu();
void		decompter();
void		initOpcode();
Uint16		readOpcode();
Uint8		loadGame(char *filename);
void		loadFont();

#endif
