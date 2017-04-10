/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoko <yoko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:17:47 by yoko              #+#    #+#             */
/*   Updated: 2017/04/07 22:57:24 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ctrl_d(t_input *input)
{
	if (I->bufpos == I->prompt2len && !ft_strlen(&(I->line[I->bufpos])))
	{
		if (I->prompt == 0)
			return (1);
		else if (I->prompt == 1)
			return (2);
	}
	return (0);
}

static int	getline_ctrl_d(t_shell *sh, t_input *input, t_autocomp *autoc)
{
	int i;

	if ((i = ctrl_d(input)) != 0)
	{
		if (i == 1 && (sh->parser->eof = 1))
			return (1);
		if (i == 2 && ft_endgetlineloop(sh, input, autoc))
			return (2);
	}
	return (0);
}

static int	getline_enter(t_input *input)
{
	I->end = 1;
	return (SUCCESS);
}

int			getline_loop(t_shell *sh, t_input *input, char *buf,
															t_autocomp *autoc)
{
	int				i;
	unsigned long	*buff_convert;

	while (42 && (I->bufposmax <= I->buffsize))
	{
		I->ret = NO_ACTION;
		ft_bzero(buf, READBUFSIZE);
		if (read(0, buf, READBUFSIZE) == -1)
			return (0);
		buff_convert = (unsigned long *)buf;
		if (*buff_convert == CAPS_ENTER)
			return (getline_enter(input));
		else if (*buff_convert == CAPS_CTRL_D)
		{
			if ((i = getline_ctrl_d(sh, input, autoc)) > 0)
				return (i - 1);
		}
		else if (*buff_convert == CAPS_CTRL_C &&
											ft_endgetlineloop(sh, input, autoc))
			return (2);
		else if (!linedit_inputkeyhook(I, autoc, buf))
			getline_put_line(I, buf, sh, autoc);
	}
	return (0);
}
