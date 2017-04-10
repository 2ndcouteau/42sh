/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedit_next_prev_word.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 10:25:01 by qrosa             #+#    #+#             */
/*   Updated: 2017/04/10 16:25:27 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		previous_word(t_input *input)
{
	if (I->bufpos > I->prompt2len)
	{
		while (ft_isspace(I->line[I->bufpos]) && I->bufpos >= I->prompt2len)
			I->bufpos--;
		while (!ft_isspace(I->line[I->bufpos]) && I->bufpos >= I->prompt2len)
			I->bufpos--;
		while (ft_isspace(I->line[I->bufpos]) && I->bufpos >= I->prompt2len)
			I->bufpos--;
		I->bufpos++;
		I->ret = CURSOR_O;
		return (SUCCESS);
	}
	return (ERROR);
}

int		next_word(t_input *input)
{
	if (I->bufpos < (int)ft_strlen(I->line))
	{
		while (!ft_isspace(I->line[I->bufpos]) &&
											I->bufpos < (int)ft_strlen(I->line))
			I->bufpos++;
		while (ft_isspace(I->line[I->bufpos]) &&
											I->bufpos < (int)ft_strlen(I->line))
			I->bufpos++;
		I->ret = CURSOR_O;
		return (SUCCESS);
	}
	return (ERROR);
}
