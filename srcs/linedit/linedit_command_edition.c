/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedit_command_edition.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 17:03:53 by qrosa             #+#    #+#             */
/*   Updated: 2017/03/23 17:44:45 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int					(*g_term_command_edition[NB_TERM_COMMAND_EDITION])
															(t_input *input) =
{
	linedit_cut,
	linedit_cut_all_line,
	linedit_cut,
	linedit_paste,
	linedit_bspace,
	linedit_del
};

static const long int	g_term_value_edition[NB_TERM_COMMAND_EDITION] = {
	CAPS_CTRL_K,
	CAPS_CTRL_U,
	CAPS_CTRL_X,
	CAPS_CTRL_Y,
	CAPS_BSPACE,
	CAPS_DEL
};

int		linedit_command_edition(t_input *input, long int *buff_convert)
{
	int	cpt;

	cpt = 0;
	while (cpt < NB_TERM_COMMAND_EDITION)
	{
		if (*buff_convert == g_term_value_edition[cpt])
		{
			if (g_term_command_edition[cpt](input))
				return (ERROR);
			return (SUCCESS);
		}
		cpt++;
	}
	return (ERROR);
}
