/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedit_printchar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:56:15 by qrosa             #+#    #+#             */
/*   Updated: 2017/04/10 16:25:44 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		linedit_printchar(t_input *input, char *buf, char *line)
{
	int i;

	if (buf[0] && ft_isprint(buf[0]))
	{
		i = 0;
		while (ft_isprint(buf[i]) && input->bufpos < (input->buffsize - 1)
		&& i < READBUFSIZE)
		{
			if (input->bufpos >= input->prompt2len)
				ft_memmove(&line[input->bufpos + 1], &line[input->bufpos],
					ft_strlen(&line[input->bufpos]));
			line[input->bufpos] = buf[i];
			input->bufpos++;
			i++;
		}
		I->ret = PRINT_AND_CURSOR;
		return (SUCCESS);
	}
	return (ERROR);
}
