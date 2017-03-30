/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoko <yoko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 22:02:44 by yoko              #+#    #+#             */
/*   Updated: 2017/02/21 19:06:03 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Options values :
** 0 = E;
** 1 = e;
** 2 = n;
** 4 = help;
** 8 = version;
*/

int			builtin_echo(char **args)
{
	unsigned int	tab_position;
	short			options;
	int				len_tab;

	options = 0;
	len_tab = ft_tablen(args);
	tab_position = check_option_echo(args, len_tab, &options);
	print_echo_line(args, len_tab, tab_position, options);
	return (SUCCESS);
}
