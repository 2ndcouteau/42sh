/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/04/07 21:16:12 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	open_write_f_history(t_dict *env)
{
	int			fd;
	char		*home;
	char		*name;

	name = NULL;
	fd = -1;
	if ((home = ft_getenv(env, "HOME")) && *home && *home == '/')
		name = ft_strjoin(home, "/.42sh_history");
	if (name)
	{
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC,
			S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR);
		free(name);
	}
	if (fd <= 2)
		fd = open("/tmp/.42sh_history", O_WRONLY | O_CREAT | O_TRUNC,
				S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR);
	return (fd);
}

static void	new_history_file(t_history *hist, t_dict *env)
{
	int	fd;
	int	size;

	fd = open_write_f_history(env);
	size = list_len(&hist->head);
	while (hist)
	{
		strchr_replace(hist->value, '\n', 26);
		if (size <= HIST_SIZE)
			ft_fdprintf(fd, "%s:%s\n", hist->key, hist->value);
		hist = (hist->head.next) ?
		(GET_NODE((hist->head.next), t_history, head)) : NULL;
		size--;
	}
	close(fd);
}

char		ft_strisdigit(char *s)
{
	char		*str;
	long int	i;

	str = s;
	if (*str == '-')
		str++;
	while (*str && ft_isdigit(*str))
		str++;
	if ((*str) || (i = ft_atoi(s)) > INT_MAX || i < INT_MIN)
	{
		ft_fdprintf(2, "42sh: exit: %s: numeric argument required\n", s);
		return (0);
	}
	return (1);
}

int			ft_exit(t_shell *sh, t_processes *proc)
{
	int		status;

	if (sh->bg_jobs)
		return (ft_fdprintf(2, "42sh: you have suspended jobs!\n"));
	ft_putendl_fd("exit 42sh", 2);
	if (g_debug[0])
		ft_fdprintf(g_debug[1], "status d'exit = {%d}\n", sh->status);
	if (proc && proc->cmds && proc->cmds->argv
	&& ft_strequ(proc->cmds->argv[0], "exit") && proc->cmds->argv[1])
		status = (!ft_strisdigit(proc->cmds->argv[1]))
			? 255 : (ft_atoi(proc->cmds->argv[1]));
	else if (sh)
		status = sh->status;
	else
		status = 0;
	new_history_file(sh->history, sh->options->env);
	destroy_shell(&sh);
	if (g_debug[0])
		ft_fdprintf(g_debug[1], "status d'exit :{%d}\n", status);
	exit(status);
}
