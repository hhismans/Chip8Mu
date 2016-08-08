/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 16:52:09 by hhismans          #+#    #+#             */
/*   Updated: 2016/08/07 17:08:06 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"
#include <string.h>

void initCpu()
{
	memset(cpu.memory, 0, sizeof(Uint8) * MEMORYSIZE);
	memset(cpu.V, 0, sizeof(Uint8) * NREGISTER);
	memset(cpu.jump, 0, sizeof(Uint16) * NREGISTER);
	cpu.pc = STARTADRESS;
	cpu.jumpCounter = 0;
	cpu.gameCounter = 0;
	cpu.soundCounter = 0;
	cpu.I = 0;
}

void decompter()
{
	if (cpu.gameCounter > 0)
		cpu.gameCounter--;
	if (cpu.soundCounter > 0)
		cpu.soundCounter--;
}

Uint16 readOpcode()
{
	return ((cpu.memory[cpu.pc] << 8) + cpu.memory[cpu.pc + 1])
}

void	initOpcode()
{
	opc.masque[0] = 0x0000; opc.id[0] = 0x0FFF; /*0NNN*/
	opc.masque[1] = 0xFFFF; opc.id[0] = 0x00E0; /*00E0*/
	opc.masque[2] = 0xFFFF; opc.id[0] = 0x00EE; /*00EE*/
	opc.masque[3] = 0xF000; opc.id[0] = 0x1000; /*1NNN*/
	opc.masque[4] = 0xF000; opc.id[0] = 0x2000; /*2NNN*/
	opc.masque[5] = 0xF000; opc.id[0] = 0x3000; /*3XNN*/
	opc.masque[6] = 0xF000; opc.id[0] = 0x4000; /*4XNN*/
	opc.masque[7] = 0xF00F; opc.id[0] = 0x5000; /*5XY0*/
	opc.masque[8] = 0xF000; opc.id[0] = 0x6000; /*6XNN*/
	opc.masque[9] = 0xF000; opc.id[0] = 0x7000; /*7XNN*/
	opc.masque[10] = 0xF00F; opc.id[0] = 0x8000; /*8XY0*/
	opc.masque[11] = 0xF00F; opc.id[0] = 0x8001; /*8XY1*/
	opc.masque[12] = 0xF00F; opc.id[0] = 0x8002; /*8XY2*/
	opc.masque[13] = 0xF00F; opc.id[0] = 0x8003; /*8XY3*/
	opc.masque[14] = 0xF00F; opc.id[0] = 0x8004; /*8XY4*/
	opc.masque[15] = 0xF00F; opc.id[0] = 0x8005; /*8XY5*/
	opc.masque[16] = 0xF00F; opc.id[0] = 0x8006; /*8XY6*/
	opc.masque[17] = 0xF00F; opc.id[0] = 0x8007; /*8XY7*/
	opc.masque[18] = 0xF00F; opc.id[0] = 0x800E; /*8XYE*/
	opc.masque[19] = 0xF00F; opc.id[0] = 0x9000; /*9XY0*/
	opc.masque[20] = 0xF000; opc.id[0] = 0xA000; /*ANNN*/
	opc.masque[21] = 0xF000; opc.id[0] = 0xB000; /*BNNN*/
	opc.masque[22] = 0xF000; opc.id[0] = 0xC000; /*CXNN*/
	opc.masque[23] = 0xF000; opc.id[0] = 0xD000; /*DXYN*/
	opc.masque[24] = 0xF0FF; opc.id[0] = 0xE09E; /*EX9E*/
	opc.masque[25] = 0xF0FF; opc.id[0] = 0xE0A1; /*EXA1*/
	opc.masque[26] = 0xF0FF; opc.id[0] = 0xF007; /*FX07*/
	opc.masque[27] = 0xF0FF; opc.id[0] = 0xF00A; /*FX0A*/
	opc.masque[28] = 0xF0FF; opc.id[0] = 0xF015; /*FX15*/
	opc.masque[29] = 0xF0FF; opc.id[0] = 0xF018; /*FX18*/
	opc.masque[30] = 0xF0FF; opc.id[0] = 0xF01E; /*FX1E*/
	opc.masque[31] = 0xF0FF; opc.id[0] = 0xF029; /*FX29*/
	opc.masque[32] = 0xF0FF; opc.id[0] = 0xF033; /*FX33*/
	opc.masque[33] = 0xF0FF; opc.id[0] = 0xF055; /*FX55*/
	opc.masque[34] = 0xF0FF; opc.id[0] = 0xF065; /*FX65*/
}
