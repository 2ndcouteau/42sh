/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/01/19 12:29:02 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		chk_redir(t_redir *red)
{
	while (red)
	{
		if (red->rtype == REDOUT)
		{
			if (redir_out(red, 0))
				return (1);
		}
		else if (red->rtype == REDAPPEND)
		{
			if (redir_out(red, 1))
				return (1);
		}
		else if (red->rtype == REDIN)
		{
			if (redir_in(red))
				return (1);
		}
		else if (red->rtype == HEREDOC)
			if (redir_heredoc(red))
				return (1);
		red = ((red->head.next)) ?
		GET_NODE((red->head.next), t_redir, head) : NULL;
	}
	return (0);
}

int		redir(t_processes *proc, int fd[4])
{
	if (proc->head.next)
	{
		close(fd[2]);
		dup2(fd[3], STDOUT_FILENO);
	}
	if (chk_redir(proc->redir))
		return (1);
	return (0);
}

void	close_redir(t_redir *red)
{
	while (red)
	{
		if (red->rtype == REDIN)
		{
			dup2(red->sav_fd, red->fd_to_redir);
			if (*red->arg != '&')
				close(red->new_fd);
			close(red->sav_fd);
		}
		else if (red->rtype == HEREDOC)
		{
			dup2(red->sav_fd, red->fd_to_redir);
			close(red->sav_fd);
		}
		else
		{
			dup2(red->sav_fd, red->fd_to_redir);
			if (*red->arg != '&')
				close(red->new_fd);
			close(red->sav_fd);
		}
		red = ((red->head.prev)) ?
		GET_NODE((red->head.prev), t_redir, head) : NULL;
	}
}
