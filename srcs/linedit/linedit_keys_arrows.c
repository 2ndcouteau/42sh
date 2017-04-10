/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedit_keys_arrows.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:18:42 by amoreilh          #+#    #+#             */
/*   Updated: 2017/04/10 16:23:59 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		arrow_left(t_input *input)
{
	if (I->bufpos > I->prompt2len)
	{
		input->bufpos--;
		I->ret = CURSOR_O;
		return (SUCCESS);
	}
	return (ERROR);
}

int		arrow_right(t_input *input)
{
	if (input->bufpos < input->bufposmax)
	{
		input->bufpos++;
		I->ret = CURSOR_O;
		return (SUCCESS);
	}
	return (ERROR);
}

int		alt_arrow_up(t_input *input)
{
	if ((input->bufpos - input->termw) >= input->prompt2len)
		input->bufpos -= input->termw;
	else if (input->bufpos >= input->termw)
		input->bufpos = input->prompt2len;
	else
		return (ERROR);
	I->ret = CURSOR_O;
	return (SUCCESS);
}

int		alt_arrow_down(t_input *input)
{
	if ((input->bufpos + input->termw) <= input->bufposmax)
		input->bufpos += input->termw;
	else if ((input->bufposmax >= input->termw) &&
						((input->bufposmax / input->termw) -
										(input->bufpos / input->termw) > 0))
		I->bufpos = I->bufposmax;
	else
		return (ERROR);
	I->ret = CURSOR_O;
	return (SUCCESS);
}
