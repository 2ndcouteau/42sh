/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_option_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:13:29 by qrosa             #+#    #+#             */
/*   Updated: 2017/02/21 19:06:54 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

short	check_option_echo(char **args, size_t len_tab, short *options)
{
	unsigned int	i;
	bool			mark;

	i = 1;
	mark = 0;
	while (i < len_tab && mark == 0)
	{
		if (!is_valid_option(args[i], len_tab))
		{
			set_option(args[i], options);
			i++;
		}
		else
			mark = 1;
	}
	return (i);
}
