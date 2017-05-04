/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activ_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/04/10 19:10:52 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		debug(int n, char *path)
{
	g_debug[0] = 1;
	if (n == 1)
	{
		if (!isatty(g_debug[1] = open(path, O_WRONLY)))
		{
			g_debug[0] = 0;
			return ;
		}
		ft_fdprintf(g_debug[1], "\n\033[93m___________DEBUG_________\033[0m\n");
	}
	else if (n == 0)
	{
		ft_fdprintf(g_debug[1], "\n\033[93m___________END__________\033[0m\n");
		close(g_debug[1]);
	}
}
