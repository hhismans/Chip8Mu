/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:08:25 by hhismans          #+#    #+#             */
/*   Updated: 2016/08/07 17:52:47 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cpu.h"
#include "opcode.h"
#include "pixel.h"

//docs in french, comment may be in french
// input : 	Uint8 b[]
//			b1=T b2=Z b3=Y b4=Noopcode toocall
//
void opcode0(Uint8 b[]){} 				//never call

void opcode1(Uint8 b[]){cleanScreen(); }	//00E0 clean screen

void opcode2(Uint8 b[]){
	if (cpu.jumpCounter > 0)
	{
		cpu.jumpCounter--;
		cpu.pc = cpu.jump[cpu.jumpCounter];
	}
	else
		fprintf(stderr, "Error, notenought jump!");
		
}				//00EE Retourne a partir dune sous fonction

void opcode3(Uint8 b[]){ cpu.pc = (b[2]<<8)+ (b[1]<<4) + b[0] - 2; } // 1NNN effectue un saut a l'adresse NNN

void opcode4(Uint8 b[]){
	cpu.jump[cpu.jumpCounter] = cpu.pc;
	if (cpu.jumpCounter < 15)
		cpu.jumpCounter++;
	else
		fprintf(stderr, "Error, too many jump!");
	cpu.pc = (b[2] << 8) + (b[1] << 4) + b[0] - 2;
} // 2NNN execute le sous programme en NNN 

void opcode5(Uint8 b[]){
	if (cpu.V[b[2]] == (b[1] << 4) + b[0])
		cpu.pc+=2;
}

void opcode6(Uint8 b[]){
	if (cpu.V[b[2]] != (b[1] << 4) + b[0])
		cpu.pc+=2;
} // 4XNN Saute a k;instru suicante si VX et NN sont diff

void opcode7(Uint8 b[]){
	if (cpu.V[b[2]] == cpu.V[b[1]])
		cpu.pc+=2;
} // 5XY0 saute a l;instu suivante si VX et VY sont egaux

void opcode8(Uint8 b[]){
	cpu.V[b[2]] = (b[1] << 4) + b[0];
} // 6XNN  defini VX a NN

void opcode9(Uint8 b[]){
	cpu.V[b[2]] += (b[1] << 4) + b[0];
}// 7XNN ajoute NN a vx

void opcode10(Uint8 b[]){ cpu.V[b[2]] = cpu.V[b[1]]; } // 8XY0 defini VX = VY

void opcode11(Uint8 b[]){
	cpu.V[b[2]] = cpu.V[b[1]] | cpu.V[b[2]];
} // 8XY1 deini VX a VX OR VY

void opcode12(Uint8 b[]){
	cpu.V[b[2]] = cpu.V[b[1]] & cpu.V[b[2]];
} // 8XY2 defini VX a VX AND VY

void opcode13(Uint8 b[]){
	cpu.V[b[2]] = cpu.V[b[1]] ^ cpu.V[b[2]];
} // 8XY3 defini VX a VX XOR VY

void opcode14(Uint8 b[]){
	if (cpu.V[b[2]] + cpu.V[b[1]] > 0xFF)
		cpu.V[0xF] = 1;
	else
		cpu.V[0xF] = 0;
	cpu.V[b[2]] += cpu.V[b[1]];
} // 8XY4 ajoute VY a VX, defini VF a 1 si depassement memoire ou 0 sinon

void opcode15(Uint8 b[]){
	if (cpu.V[b[2]] < cpu.V[b[1]])
		cpu.V[0xF] = 0;
	else
		cpu.V[0xF] = 1;
	cpu.V[b[2]] -= cpu.V[b[1]];
} // 8XY5 VY est soustrait de VX, VF a 0 si il y a emprut, a 1 sinon

void opcode16(Uint8 b[]){
	cpu.V[0xF] = 1 & cpu.V[b[2]];
	cpu.V[b[2]] = cpu.V[b[2]] >> 1;
} // 8XY6 decale VX a gauche de 1, VF est fixe a la valeur du bit de poid le plus faible avant decalage

void opcode17(Uint8 b[]){
	if (cpu.V[b[2]] > cpu.V[b[1]])
		cpu.V[0xF] = 0;
	else
		cpu.V[0xF] = 1;
	cpu.V[b[2]] = cpu.V[b[1]] - cpu.V[b[2]];
} // 8XY7 VX = VY - VX VF = 0 si resultat negatif

void opcode18(Uint8 b[]){
	cpu.V[0xF] = cpu.V[b[2]] >> 7;//(1 << 7) & cpu.V[b[2]];
	cpu.V[b[2]] = cpu.V[b[2]] >> 1;
} // 8XYE decale VX a gauche de 1, VF est fixe a la valeur du bit de poid le plus faible avant decalage

void opcode19(Uint8 b[]){
	if (cpu.V[b[2]] != cpu.V[b[1]])
		cpu.pc+=2;
} //9XY0 jump a l'opcode suivant si VX != VY

void opcode20(Uint8 b[]){
	cpu.I = (b[2] << 8) + (b[1] << 4) + b[0];
} //ANNN affecte NNN a I

void opcode21(Uint8 b[]){
	cpu.pc = (b[2] << 8) + (b[1] << 4) + b[0] + cpu.V[0];
	cpu.pc -=2;
}

void opcode22(Uint8 b[]){ 
	cpu.V[b[2]] = rand() % ((b[1]<<4) + b[0]);
} // CXNN defini VX a un nbr aleatoire < NN

void opcode23(Uint8 b[]){ // DXYN Dessine sprite
	/*Dessine un sprite aux coordonnées (VX, VY). 
		Le sprite a une largeur de 8 pixels et une hauteur de pixels N. 
		Chaque rangée de 8 pixels est lue comme codée en binaire à partir de l'emplacement mémoire. 
		I ne change pas de valeur après l'exécution de cette instruction.
*/
	Uint8	VX = cpu.V[b[2]];
	Uint8	VY = cpu.V[b[1]];
	Uint8	line = 0; // represente une ligne de sprite en binaire.
	int x, y;
	cpu.V[0xF] = 0; // sera mit a 1 si cas deja allume
	for (int i = 0; i < b[0]; i++) // cf doc, hheight sprite = bit de poids faible
	{
		line = cpu.memory[cpu.I + i];// get line in binary (Uint8)
		y = (VY + i) % CHIP8HEIGHT;// must not be > height CHIP8
			for (int j = 0, decal = 7; j < 8; j++, decal--)
			{
				x=(VX + j) % CHIP8WIDTH;
				if ((line) & (0x1 << decal)) // if jth bit is 1j
				{
					if (pixel[x][y].color == WHITE)
					{
						pixel[x][y].color = BLACK;
						cpu.V[0xF] = 1; // sera mit a 1 si cas deja allume
					}
					else
						pixel[x][y].color = WHITE;
				}
			}
	}
} // DXYN draw sprite
void opcode24(Uint8 b[]){

} // EX9E saute a l;instructiob suicante si la clee stockee dans VX est pressee
void opcode25(Uint8 b[]){

} // EXA1 saute a l;instructiob suicante si la clee stockee dans VX est pressee

void opcode26(Uint8 b[]){
	cpu.V[b[2]] = cpu.gameCounter;
} //FX07 defini VX a gamecounter

void opcode27(Uint8 b[]){

} // FX0A

void opcode28(Uint8 b[]){
	cpu.gameCounter = cpu.V[b[2]];
} // FX15 defini gamcounter a VX

void opcode29(Uint8 b[]){
	cpu.soundCounter = cpu.V[b[2]];
} // FX18 defini soundcounter a VX

void opcode30(Uint8 b[]){
	if (cpu.I + cpu.V[b[2]] > 0xFFF)
		cpu.V[0xF] = 1;
	else
		cpu.V[0xF] = 0;
	cpu.I += cpu.V[b[2]];
} // FX1E   I += VX

void opcode31(Uint8 b[]){ 
	cpu.I = cpu.V[b[2]]*5; // drawing stuff are in 5height
} // FX29  cf doc caractere stocke en memoire

void opcode32(Uint8 b[]){
	cpu.memory[cpu.I] = (cpu.V[b[2]] - cpu.V[b[2]]%100) / 100;
	cpu.memory[cpu.I + 1] = ((cpu.V[b[2]] - cpu.V[b[2]]%10)/10)%10;
	cpu.memory[cpu.I + 2] = cpu.V[b[2]] % 10;
} // FX33 stocke dans la memoire une representation decimale de VX (chaine de caractere like, mais pas en ascii)

void opcode33(Uint8 b[]){
	for (Uint8 i = 0; i < b[2];i++)
	{
		cpu.memory[cpu.I + i] = cpu.V[i];
	}
} // FX55 stocke v0 a VX en mememoire a partir de l'adresse de I

void opcode34(Uint8 b[]){
	for (Uint8 i = 0; i < b[2];i++)
	{
		cpu.V[i] = cpu.memory[cpu.I + i];
	}
} // FX55 stocke v0 a VX en mememoire a partir de l'adresse de I

Uint8 opcodeNumber(Uint16 opcode)
{
	Uint8 ret;
	for(ret = 0; ret < NBROPCODE; ret++)
	{
		if ((opc.masque[ret] & opcode) == opc.id[ret])
		{
			printf("OPCODE FIND ! Number %d\n", ret);
			break;
		}
	}
	if (ret >= NBROPCODE)
	{
		fprintf(stderr, "ERROR OPCODE NOT FOUND %x \n", opcode);
		exit(-1);
	}
	return ret;
}

void execOpcode(Uint16 opcode)
{
	Uint8 b[3];
	b[0] = (opcode & 0x000F);
	b[1] = (opcode & 0x00F0) >> 4;
	b[2] = (opcode & 0x0F00) >> 8;

	printf("exec op code %x\n", opcode);
	opcodeFctTab[opcodeNumber(opcode)](b);
	cpu.pc += 2;
}
