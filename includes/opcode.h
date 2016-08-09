/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcode.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:08:25 by hhismans          #+#    #+#             */
/*   Updated: 2016/08/07 17:52:47 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPCODE_H
# define OPCODE_H



void execOpcode(Uint16 opcode);
Uint8 opcodeNumber(Uint16 opcode);

void opcode0();
void opcode1();
void opcode2();
void opcode3();
void opcode4();
void opcode5();
void opcode6();
void opcode7();
void opcode8();
void opcode9();
void opcode10();
void opcode11();
void opcode12();
void opcode13();
void opcode14();
void opcode15();
void opcode16();
void opcode17();
void opcode18();
void opcode19();
void opcode20();
void opcode21();
void opcode22();
void opcode23();
void opcode24();
void opcode25();
void opcode26();
void opcode27();
void opcode28();
void opcode29();
void opcode30();
void opcode31();
void opcode32();
void opcode33();
void opcode34();

void (*opcodeFctTab[]) () =
{
	&opcode0,
	&opcode1,
	&opcode2,
	&opcode3,
	&opcode4,
	&opcode5,
	&opcode6,
	&opcode7,
	&opcode8,
	&opcode9,
	&opcode10,
	&opcode11,
	&opcode12,
	&opcode13,
	&opcode14,
	&opcode15,
	&opcode16,
	&opcode17,
	&opcode18,
	&opcode19,
	&opcode20,
	&opcode21,
	&opcode22,
	&opcode23,
	&opcode24,
	&opcode25,
	&opcode26,
	&opcode27,
	&opcode28,
	&opcode29,
	&opcode30,
	&opcode31,
	&opcode32,
	&opcode33,
	&opcode34
};
#endif
