/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedit_del_supr_clear.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 15:24:33 by amoreilh          #+#    #+#             */
/*   Updated: 2017/04/10 16:23:19 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		linedit_del(t_input *input)
{
	if (input->bufpos >= input->prompt2len)
		ft_memmove(&(I->line)[input->bufpos], &(I->line)[input->bufpos + 1],
			ft_strlen(&(I->line)[input->bufpos]));
	else
		return (ERROR);
	I->ret = PRINT_AND_CURSOR;
	return (SUCCESS);
}

int		linedit_bspace(t_input *input)
{
	if (I->bufpos > I->prompt2len)
	{
		input->bufpos--;
		ft_memmove(&(I->line)[input->bufpos], &(I->line)[input->bufpos + 1],
			ft_strlen(&(I->line)[input->bufpos]));
		I->ret = PRINT_AND_CURSOR;
		return (SUCCESS);
	}
	return (ERROR);
}

int		linedit_clear(t_input *input, t_autocomp *autoc)
{
	ft_printf("\033[2J");
	input->savecursy = 1;
	ft_printbuf(input, autoc);
	return (SUCCESS);
}
