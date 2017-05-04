/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 18:00:29 by nboulaye          #+#    #+#             */
/*   Updated: 2017/04/27 18:50:41 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

static int		fork_n_eval_suite(t_shell *shell, int fds_out[2])
{
	pid_t	pid;

	if (!(pid = fork()))
		child_eval(fds_out, shell);
	else if (pid == -1 && ft_fdprintf(2, "fork error\n"))
		exit(1);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	return (pid);
}

static char		*fork_n_eval(t_shell *shell)
{
	int		saved_out;
	int		fds_out[2];
	pid_t	pid;
	char	*out;
	int		status;

	out = NULL;
	signal(SIGINT, SIG_IGN);
	if (STATE(shell->parser) != ST_ERR)
	{
		saved_out = dup(STDOUT_FILENO);
		if (pipe(fds_out) && ft_fdprintf(2, "out-pipe error\n"))
			return (NULL);
		pid = fork_n_eval_suite(shell, fds_out);
		if (waitpid(pid, &status, 0) == -1 && ft_fdprintf(2, "wait error\n"))
			exit(1);
		if (read_n_cat(fds_out, saved_out, &out) == -1)
			return (NULL);
	}
	else
		ft_fdprintf(2, "parse error.");
	destroy_parser(&(shell->parser));
	signal(SIGINT, SIG_DFL);
	return (out);
}

char			*ft_eval(t_shell *shell, char *code)
{
	if (!code)
		return (NULL);
	if (shell->parser == NULL)
		if (!(shell->parser = new_parser(shell->options)))
			return (NULL);
	if (shell->parser->orig)
		free(shell->parser->orig);
	shell->parser->orig = code ? ft_strdup(code) : NULL;
	ft_fdprintf(g_debug[1], F_GRE);
	parse(shell, 0);
	ft_fdprintf(g_debug[1], F_END);
	if (IS_ML(shell->parser))
	{
		ft_fdprintf(2, "code not well formated.");
		return (NULL);
	}
	return (fork_n_eval(shell));
}
