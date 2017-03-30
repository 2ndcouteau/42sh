/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedit_inputkeyhook.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoko <yoko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:50:11 by yoko              #+#    #+#             */
/*   Updated: 2017/03/27 21:27:07 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		linedit_inputkeyhook(t_input *input, t_autocomp *autoc, char *buf)
{
	long int	*buff_convert;

	buff_convert = (int long *)buf;
	printf("\nThe values_touch = %d %d %d %d %d %d %d %d\n\n\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
	printf("The values_touch %s = %ld\n", buf, *buff_convert);
	if (!linedit_printchar(I, buf, I->line))		//
		return (SUCCESS);					//
	if (!linedit_command_edition(I, buff_convert))
		return (SUCCESS);
	if (!linedit_command_cursor(I, buff_convert))
		return (SUCCESS);
	if (*buff_convert == CAPS_CTRL_L)
		return (linedit_clear(I, autoc));
	put_stdout("bl");
	return (ERROR);
}
