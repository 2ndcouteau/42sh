/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedit_home_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:00:17 by qrosa             #+#    #+#             */
/*   Updated: 2017/04/10 16:23:26 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	home_position(t_input *input)
{
	if (I->bufpos > I->prompt2len)
	{
		I->bufpos = I->prompt2len;
		I->ret = CURSOR_O;
		return (SUCCESS);
	}
	return (ERROR);
}

int	end_position(t_input *input)
{
	if (I->bufpos < I->bufposmax)
	{
		I->bufpos = I->bufposmax;
		I->ret = CURSOR_O;
		return (SUCCESS);
	}
	return (ERROR);
}
