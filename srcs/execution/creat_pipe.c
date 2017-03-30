/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/02/18 18:26:33 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	creat_pipe(int fd[4])
{
	fd[0] = dup(STDOUT_FILENO);
	fd[1] = dup(STDIN_FILENO);
	if (g_debug[0])
		ft_fdprintf(g_debug[1], "creat PIPE\
		dup stdout : %d, stdin :%d\n", fd[0], fd[1]);
	if (pipe(&fd[2]) == -1)
	{
		ft_putstr_fd("\033[31mpipe failed\033[0m\n", 2);
		return (1);
	}
	return (0);
}
