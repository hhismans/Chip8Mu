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
	loadFont();
	initOpcode();
	if (!loadGame(GAMENAME)){
		exit(-1);
	}
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
	return ((cpu.memory[cpu.pc] << 8) + cpu.memory[cpu.pc + 1]);
}

void	initOpcode()
{
	opc.masque[0] = 0x0000; opc.id[0] = 0x0FFF; /*0NNN*/
	opc.masque[1] = 0xFFFF; opc.id[1] = 0x00E0; /*00E0*/
	opc.masque[2] = 0xFFFF; opc.id[2] = 0x00EE; /*00EE*/
	opc.masque[3] = 0xF000; opc.id[3] = 0x1000; /*1NNN*/
	opc.masque[4] = 0xF000; opc.id[4] = 0x2000; /*2NNN*/
	opc.masque[5] = 0xF000; opc.id[5] = 0x3000; /*3XNN*/
	opc.masque[6] = 0xF000; opc.id[6] = 0x4000; /*4XNN*/
	opc.masque[7] = 0xF00F; opc.id[7] = 0x5000; /*5XY0*/
	opc.masque[8] = 0xF000; opc.id[8] = 0x6000; /*6XNN*/
	opc.masque[9] = 0xF000; opc.id[9] = 0x7000; /*7XNN*/
	opc.masque[10] = 0xF00F; opc.id[10] = 0x8000; /*8XY0*/
	opc.masque[11] = 0xF00F; opc.id[11] = 0x8001; /*8XY1*/
	opc.masque[12] = 0xF00F; opc.id[12] = 0x8002; /*8XY2*/
	opc.masque[13] = 0xF00F; opc.id[13] = 0x8003; /*8XY3*/
	opc.masque[14] = 0xF00F; opc.id[14] = 0x8004; /*8XY4*/
	opc.masque[15] = 0xF00F; opc.id[15] = 0x8005; /*8XY5*/
	opc.masque[16] = 0xF00F; opc.id[16] = 0x8006; /*8XY6*/
	opc.masque[17] = 0xF00F; opc.id[17] = 0x8007; /*8XY7*/
	opc.masque[18] = 0xF00F; opc.id[18] = 0x800E; /*8XYE*/
	opc.masque[19] = 0xF00F; opc.id[19] = 0x9000; /*9XY0*/
	opc.masque[20] = 0xF000; opc.id[20] = 0xA000; /*ANNN*/
	opc.masque[21] = 0xF000; opc.id[21] = 0xB000; /*BNNN*/
	opc.masque[22] = 0xF000; opc.id[22] = 0xC000; /*CXNN*/
	opc.masque[23] = 0xF000; opc.id[23] = 0xD000; /*DXYN*/
	opc.masque[24] = 0xF0FF; opc.id[24] = 0xE09E; /*EX9E*/
	opc.masque[25] = 0xF0FF; opc.id[25] = 0xE0A1; /*EXA1*/
	opc.masque[26] = 0xF0FF; opc.id[26] = 0xF007; /*FX07*/
	opc.masque[27] = 0xF0FF; opc.id[27] = 0xF00A; /*FX0A*/
	opc.masque[28] = 0xF0FF; opc.id[28] = 0xF015; /*FX15*/
	opc.masque[29] = 0xF0FF; opc.id[29] = 0xF018; /*FX18*/
	opc.masque[30] = 0xF0FF; opc.id[30] = 0xF01E; /*FX1E*/
	opc.masque[31] = 0xF0FF; opc.id[31] = 0xF029; /*FX29*/
	opc.masque[32] = 0xF0FF; opc.id[32] = 0xF033; /*FX33*/
	opc.masque[33] = 0xF0FF; opc.id[33] = 0xF055; /*FX55*/
	opc.masque[34] = 0xF0FF; opc.id[34] = 0xF065; /*FX65*/
}

void loadFont()
{
	cpu.memory[0]=0xF0;cpu.memory[1]=0x90;cpu.memory[2]=0x90;cpu.memory[3]=0x90; cpu.memory[4]=0xF0; // O
	cpu.memory[5]=0x20;cpu.memory[6]=0x60;cpu.memory[7]=0x20;cpu.memory[8]=0x20;cpu.memory[9]=0x70; // 1
	cpu.memory[10]=0xF0;cpu.memory[11]=0x10;cpu.memory[12]=0xF0;cpu.memory[13]=0x80; cpu.memory[14]=0xF0; // 2
	cpu.memory[15]=0xF0;cpu.memory[16]=0x10;cpu.memory[17]=0xF0;cpu.memory[18]=0x10;cpu.memory[19]=0xF0; // 3
	cpu.memory[20]=0x90;cpu.memory[21]=0x90;cpu.memory[22]=0xF0;cpu.memory[23]=0x10;cpu.memory[24]=0x10; // 4
	cpu.memory[25]=0xF0;cpu.memory[26]=0x80;cpu.memory[27]=0xF0;cpu.memory[28]=0x10;cpu.memory[29]=0xF0; // 5
	cpu.memory[30]=0xF0;cpu.memory[31]=0x80;cpu.memory[32]=0xF0;cpu.memory[33]=0x90;cpu.memory[34]=0xF0; // 6
	cpu.memory[35]=0xF0;cpu.memory[36]=0x10;cpu.memory[37]=0x20;cpu.memory[38]=0x40;cpu.memory[39]=0x40; // 7
	cpu.memory[40]=0xF0;cpu.memory[41]=0x90;cpu.memory[42]=0xF0;cpu.memory[43]=0x90;cpu.memory[44]=0xF0; // 8
	cpu.memory[45]=0xF0;cpu.memory[46]=0x90;cpu.memory[47]=0xF0;cpu.memory[48]=0x10;cpu.memory[49]=0xF0; // 9
	cpu.memory[50]=0xF0;cpu.memory[51]=0x90;cpu.memory[52]=0xF0;cpu.memory[53]=0x90;cpu.memory[54]=0x90; // A
	cpu.memory[55]=0xE0;cpu.memory[56]=0x90;cpu.memory[57]=0xE0;cpu.memory[58]=0x90;cpu.memory[59]=0xE0; // B
	cpu.memory[60]=0xF0;cpu.memory[61]=0x80;cpu.memory[62]=0x80;cpu.memory[63]=0x80;cpu.memory[64]=0xF0; // C
	cpu.memory[65]=0xE0;cpu.memory[66]=0x90;cpu.memory[67]=0x90;cpu.memory[68]=0x90;cpu.memory[69]=0xE0; // D
	cpu.memory[70]=0xF0;cpu.memory[71]=0x80;cpu.memory[72]=0xF0;cpu.memory[73]=0x80;cpu.memory[74]=0xF0; // E
	cpu.memory[75]=0xF0;cpu.memory[76]=0x80;cpu.memory[77]=0xF0;cpu.memory[78]=0x80;cpu.memory[79]=0x80; // F
}

Uint8 loadGame(char *filename)
{
    FILE *gamefd = NULL;
    gamefd=fopen(filename,"rb");

    if(gamefd != NULL)
    {
        fread(&cpu.memory[STARTADRESS],sizeof(Uint8)*(MEMORYSIZE-STARTADRESS), 1, gamefd);
        fclose(gamefd);
        return 1;
    }
    else
    {
      fprintf(stderr,"Problème d'ouverture du fichier");
      return 0;
    }
}

Uint8 getAction(Uint16 opcode)
{
	Uint8 id;
	int tabIndex;
	int ret = -1;
	for (tabIndex = 0; tabIndex < NBROPCODE; tabIndex++)
	{
		id = (opc.masque[tabIndex] & opcode);
		if (id == opc.id[0])
		{
			ret = tabIndex;
			break;
		}
	}
	return (ret);
}
