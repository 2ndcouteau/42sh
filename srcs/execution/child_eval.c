/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_eval.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 18:00:29 by nboulaye          #+#    #+#             */
/*   Updated: 2017/04/27 16:46:10 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	child_eval(int fds_out[2], t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	dup2(fds_out[1], STDOUT_FILENO);
	write(1, " ", 1);
	close(fds_out[0]);
	shell->script = 1;
	ft_execjobs(shell
		, shell->parser->jobs, shell->parser->opts->env, 0);
	write(fds_out[1], "\0", 1);
	close(fds_out[1]);
	exit(shell->status);
}
