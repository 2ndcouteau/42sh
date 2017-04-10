/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedit_copypaste.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:17:04 by amoreilh          #+#    #+#             */
/*   Updated: 2017/04/10 01:10:25 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		linedit_cut(t_input *input)
{
	int cut_len;

	if (I->bufpos < I->bufposmax)
	{
		I->multi = 0;
		cut_len = (int)ft_strlen(&I->line[I->bufpos]);
		ft_strdel(&(I->clipboard));
		I->clipboard = ft_strsub(input->line, I->bufpos, cut_len);
		ft_bzero((I->line + I->bufpos), cut_len);
		I->ret = PRINT_AND_CURSOR;
		return (SUCCESS);
	}
	return (ERROR);
}

int		linedit_cut_all_line(t_input *input)
{
	if (I->bufposmax > I->prompt2len)
	{
		I->multi = 0;
		ft_strdel(&(I->clipboard));
		I->clipboard = ft_strdup((I->line + I->prompt2len));
		ft_bzero((I->line + I->prompt2len), ft_strlen(I->line + I->prompt2len));
		I->bufpos = I->prompt2len;
		I->ret = PRINT_AND_CURSOR;
		return (SUCCESS);
	}
	return (ERROR);
}

int		linedit_paste(t_input *input)
{
	int pastelen;

	if (I->clipboard != NULL && I->clipboard[0] != '\0')
	{
		pastelen = ft_strlen(I->clipboard);
		while (((int)ft_strlen(I->line) + pastelen) > I->buffsize)
			linedit_reallocbuff(I);
		ft_memmove(&I->line[I->bufpos + pastelen],
			&I->line[I->bufpos],
			(int)ft_strlen(&I->line[I->bufpos]));
		ft_strncpy(&I->line[I->bufpos],
			I->clipboard, (int)ft_strlen(I->clipboard));
		I->bufpos += pastelen;
		I->ret = PRINT_AND_CURSOR;
		return (SUCCESS);
	}
	return (ERROR);
}
