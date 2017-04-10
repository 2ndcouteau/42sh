/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_direct_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:16:34 by qrosa             #+#    #+#             */
/*   Updated: 2017/04/07 22:20:00 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_direct_line(char **args, size_t len_tab,
			unsigned int tab_position, short options)
{
	while (tab_position < len_tab)
	{
		ft_putstr(args[tab_position]);
		if (tab_position + 1 < len_tab)
			ft_putchar(' ');
		tab_position += 1;
	}
	if ((options & 2) != 2)
		ft_putchar('\n');
}
