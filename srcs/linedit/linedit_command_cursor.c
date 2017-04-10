/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedit_command_cursor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 17:05:32 by qrosa             #+#    #+#             */
/*   Updated: 2017/04/07 22:58:18 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int						(*g_term_command_cursor[NB_TERM_COMMAND_CURSOR])
									(t_input *input) =
{
	home_position,
	end_position,
	bridge_tab,
	bridge_up,
	bridge_down,
	arrow_right,
	arrow_left,
	end_position,
	home_position,
	alt_arrow_up,
	alt_arrow_down,
	next_word,
	previous_word,
	alt_arrow_up,
	alt_arrow_down,
	next_word,
	previous_word
};

static const long int	g_term_value_cursor[NB_TERM_COMMAND_CURSOR] = {
	CAPS_CTRL_A,
	CAPS_CTRL_E,
	CAPS_TAB,
	CAPS_ARROW_UP,
	CAPS_ARROW_DOWN,
	CAPS_ARROW_RIGHT,
	CAPS_ARROW_LEFT,
	CAPS_END,
	CAPS_HOME,
	CAPS_ALT_UP,
	CAPS_ALT_DOWN,
	CAPS_ALT_RIGHT,
	CAPS_ALT_LEFT,
	CAPS_ALT_UP_LINUX,
	CAPS_ALT_DOWN_LINUX,
	CAPS_ALT_RIGHT_LINUX,
	CAPS_ALT_LEFT_LINUX
};

int	linedit_command_cursor(t_input *input, long int *buff_convert)
{
	int	cpt;

	cpt = 0;
	if (ft_strcmp((char*)buff_convert, "\0") == 0)
		return (ERROR);
	while (cpt < NB_TERM_COMMAND_CURSOR)
	{
		if (*buff_convert == g_term_value_cursor[cpt])
		{
			if (g_term_command_cursor[cpt](I))
				return (ERROR);
			return (SUCCESS);
		}
		cpt++;
	}
	return (ERROR);
}
