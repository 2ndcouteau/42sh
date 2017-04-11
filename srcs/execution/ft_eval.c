/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 18:00:29 by nboulaye          #+#    #+#             */
/*   Updated: 2017/04/08 19:39:08 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		child_eval(int fds[2], t_shell *shell)
{
	dup2(fds[1], STDOUT_FILENO);
	close(fds[0]);
	shell->script = 1;
	ft_execjobs(shell
		, shell->parser->jobs, shell->parser->opts->env, 0);
	write(fds[1], "\0", 1);
	close(fds[1]);
	exit(shell->status);
}

static char		*join_or_dup(char *buff, char *out, int i)
{
	buff[i] = 0;
	if (out == NULL)
		out = ft_strdup(buff);
	else
		out = ft_strjoinfree(out, ft_strdup(buff));
	return (out);
}

static int		read_n_cat(int fds[2], int saved_out, char **out)
{
	char	buff[256];
	int		i;

	*out = NULL;
	while ((i = read(fds[0], buff, 255)) == 255)
		*out = join_or_dup(buff, *out, i);
	if (i > 0)
		*out = join_or_dup(buff, *out, i);
	close(fds[1]);
	close(fds[0]);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_out);
	if (i == -1 && ft_fdprintf(2, "read error\n"))
		return (-1);
	return (0);
}

static char		*fork_n_eval(t_shell *shell)
{
	int		saved_out;
	int		fds[2];
	pid_t	pid;
	char	*out;
	int		status;

	out = NULL;
	if (STATE(shell->parser) != ST_ERR)
	{
		saved_out = dup(STDOUT_FILENO);
		if (pipe(fds) && ft_fdprintf(2, "pipe error\n"))
			return (NULL);
		if (!(pid = fork()))
			child_eval(fds, shell);
		else if (pid == -1 && ft_fdprintf(2, "fork error\n"))
			exit(1);
		if (waitpid(pid, &status, 0) == -1 && ft_fdprintf(2, "wait error\n"))
			exit(1);
		if (read_n_cat(fds, saved_out, &out) == -1)
			return (NULL);
	}
	else
		ft_fdprintf(2, "an error occured.");
	destroy_parser(&(shell->parser));
	return (out);
}

char			*ft_eval(t_shell *shell, char *code)
{
	// char	*out;
	// int		*status;

	// status = NULL;
	// out = NULL;
	if (shell->parser == NULL)
		if (!(shell->parser = new_parser(shell->options)))
			return (NULL);
	shell->parser->orig = code ? ft_strdup(code) : NULL;
	ft_fdprintf(g_debug[1], F_GRE);
	parse(shell);
	ft_fdprintf(g_debug[1], F_END);
	if (IS_ML(shell->parser))
	{
		ft_fdprintf(2, "code not well formated.");
		return (NULL);
	}
	return (fork_n_eval(shell));
}
/*
char	*ft_eval(t_shell *shell, char *code)
{
	int		fds[2];
	int		saved_out;
	char	buff[256];
	char	*out;
	int		i;
	pid_t	pid;
	int		*status;

	status = NULL;
	out = NULL;
	if (shell->parser == NULL)
		if (!(shell->parser = new_parser(shell->options)))
			return (NULL);
	shell->parser->orig = code ? ft_strdup(code) : NULL;
	ft_fdprintf(g_debug[1], F_GRE);
	parse(shell);
	ft_fdprintf(g_debug[1], F_END);
	if (!IS_ML(shell->parser))
	{
		if (STATE(shell->parser) != ST_ERR)
		{
			saved_out = dup(STDOUT_FILENO);
			if (pipe(fds))
			{
				ft_fdprintf(2, "pipe error\n");
				return (NULL);
			}
			if (!(pid = fork()))
			{
				dup2(fds[1], STDOUT_FILENO);
				close(fds[0]);
				shell->script = 1;
				ft_execjobs(shell
					, shell->parser->jobs, shell->parser->opts->env, 0);
				write(fds[1], "\0", 1);
				close(fds[1]);
				exit(shell->status);
			}
			else if (pid == -1)
			{
				ft_fdprintf(2, "fork error\n");
				exit(1);
			}
			if (waitpid(pid, status, 0) == -1)
			{
				ft_fdprintf(2, "wait error\n");
				exit(1);
			}
			while ((i = read(fds[0], buff, 255)) == 255)
			{
				buff[i] = 0;
				if (out == NULL)
					out = ft_strdup(buff);
				else
					out = ft_strjoinfree(out, ft_strdup(buff));
			}
			if (i > 0)
			{
				buff[i] = 0;
				if (out == NULL)
					out = ft_strdup(buff);
				else
					out = ft_strjoinfree(out, ft_strdup(buff));
			}
			close(fds[1]);
			close(fds[0]);
			dup2(saved_out, STDOUT_FILENO);
			close(saved_out);
			if (i == -1)
			{
				ft_fdprintf(2, "read error\n");
				return (NULL);
			}

		}
		else
			ft_fdprintf(2, "an error occured.");
		destroy_parser(&(shell->parser));
	}
	else
	{
		ft_fdprintf(2, "code not well formated.");
		return (out);
	}
	return (out);
}
*/
