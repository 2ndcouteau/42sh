/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedit_inputkeyhook.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoko <yoko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:50:11 by yoko              #+#    #+#             */
/*   Updated: 2017/04/09 18:19:20 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		linedit_inputkeyhook(t_input *input, t_autocomp *autoc, char *buf)
{
	long int	*buff_convert;

	buff_convert = (int long *)buf;
	if (!linedit_printchar(I, buf, I->line))
		return (SUCCESS);
	if (!linedit_command_edition(I, buff_convert))
		return (SUCCESS);
	if (!linedit_command_cursor(I, buff_convert))
		return (SUCCESS);
	if (*buff_convert == CAPS_CTRL_L)
		return (linedit_clear(I, autoc));
	put_stdout("bl");
	return (ERROR);
}
