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
#include "libft.h"

void initCpu()
{
	ft_memset(cpu.memory, 0, sizeof(Uint8) * MEMORYSIZE);
	ft_memset(cpu.V, 0, sizeof(Uint8) * NREGISTER);
	ft_memset(cpu.jump, 0, sizeof(Uint16) * NREGISTER);
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
