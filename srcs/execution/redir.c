/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/02/04 23:55:48 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	open_file(char *name, char append)
{
	int	new_fd;

	if (append)
	{
		if ((new_fd = open(name, O_WRONLY | O_CREAT | O_APPEND,
		S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR)) == -1)
			ft_fdprintf(2, "open failed \033[31m%s\n\033[0m", name);
	}
	else
	{
		if ((new_fd = open(name, O_WRONLY | O_CREAT | O_TRUNC,
		S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR)) == -1)
			ft_fdprintf(2, "creat failed \033[31m%s\n\033[0m", name);
	}
	return (new_fd);
}

int			redir_out(t_redir *red, int append)
{
	red->fd_to_redir = (red->fdin) ? ft_atoi(red->fdin) : STDOUT_FILENO;
	if (*red->arg == '&')
		red->new_fd = (*(red->arg + 1) == '-') ? -42 : ft_atoi(&red->arg[1]);
	else
		red->new_fd = open_file(red->arg, append);
	if (g_debug[0])
		ft_fdprintf(g_debug[1], "- - - redir in |%s| (fd = %d)\n\033[0m"
		, red->arg, red->new_fd);
	if (red->new_fd != -42 && (fcntl(red->new_fd, F_GETFL) == -1))
	{
		if (red->new_fd >= 0)
			ft_fdprintf(2, "\033[31m42sh: %d: bad file descriptor\n\033[0m"
		, red->new_fd);
		else
			ft_fdprintf(2, "\033[31m42sh: bad file descriptor\n\033[0m");
		return (1);
	}
	red->sav_fd = dup(red->fd_to_redir);
	(red->new_fd != -42) ?
	dup2(red->new_fd, red->fd_to_redir) : close(red->fd_to_redir);
	return (0);
}

int			redir_in(t_redir *red)
{
	red->fd_to_redir = (red->fdin) ? ft_atoi(red->fdin) : STDIN_FILENO;
	if (*red->arg == '&')
		red->new_fd = (*(red->arg + 1) == '-') ? -42 : ft_atoi(&red->arg[1]);
	else
		red->new_fd = open(red->arg, O_RDONLY);
	if (g_debug[0])
		ft_fdprintf(g_debug[1], "- - - redir file |%s| (fd = %d) in cmd\n"
		, red->arg, red->new_fd);
	if (red->new_fd != -42 && fcntl(red->new_fd, F_GETFL) == -1)
	{
		ft_fdprintf(2, "\033[31m42sh: no such file or directory: %s\n\033[0m"
		, red->arg);
		return (1);
	}
	red->sav_fd = dup(red->fd_to_redir);
	(red->new_fd != -42) ?
	dup2(red->new_fd, red->fd_to_redir) : close(red->fd_to_redir);
	return (0);
}

int			redir_heredoc(t_redir *red)
{
	int	fd[2];

	red->fd_to_redir = STDIN_FILENO;
	red->sav_fd = dup(red->fd_to_redir);
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("\033[31mpipe failed\033[0m\n", 2);
		return (1);
	}
	if (dup2(fd[0], red->fd_to_redir) < 0)
	{
		ft_fdprintf(2, "DUP2 error\n");
		return (1);
	}
	if (red->heredoc && *red->heredoc && ft_putendl_fd(red->heredoc, fd[1]) < 0)
	{
		ft_fdprintf(2, "Write error\n");
		return (1);
	}
	close(fd[1]);
	return (0);
}
