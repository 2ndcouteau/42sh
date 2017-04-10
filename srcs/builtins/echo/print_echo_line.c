/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_echo_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:17:04 by qrosa             #+#    #+#             */
/*   Updated: 2017/04/07 22:34:29 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_echo_line(char **args, size_t len_tab,
			unsigned int tab_position, short options)
{
	if (!print_long_options(options))
		return ;
	if ((options & 1) != 1)
		print_direct_line(args, len_tab, tab_position, options);
	else
		print_special_line(args, len_tab, tab_position, options);
}
