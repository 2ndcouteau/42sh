/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/02/24 20:40:47 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "history.h"

static char	chk_flag_hist(char *argv)
{
	char flag;

	flag = 0;
	if (*argv == '-')
		while (*(++argv))
		{
			if (*argv == 'c')
				flag = _FLAG_C;
			else if (*argv == 'd')
				flag = _FLAG_D;
			else if (*argv == '-')
				return (0);
			else
				return (-1);
		}
	return (flag);
}

static char	read_argv_hist(char **argv, int *idx_to_del)
{
	char	flag;

	flag = 0;
	if (!(*argv) || !(*(argv + 1)))
		return (0);
	argv++;
	while (argv && *argv && (flag = chk_flag_hist(*argv)) > 0)
	{
		if (flag == _FLAG_C)
			return (_FLAG_C);
		else if (flag == _FLAG_D)
		{
			if (++argv && *argv)
				*idx_to_del = ft_atoi(*argv);
			else
				break ;
		}
		argv++;
	}
	return (flag);
}

static int	trunc_hist(t_shell *shell)
{
	char	*home;
	char	*name;
	int		fd;

	destroy_history(shell->history);
	name = NULL;
	fd = -1;
	if (shell->options && shell->options->env &&
		(home = ft_getenv(shell->options->env, "HOME")) && *home)
		name = ft_strjoin(home, "/.42sh_history");
	if (name)
		fd = open(name, O_RDONLY | O_CREAT | O_TRUNC
		, S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR);
	if (!name || fd == -1)
		fd = open("/tmp/.42sh_history", O_RDONLY | O_CREAT | O_TRUNC
		, S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR);
	if (name)
		ft_strdel(&name);
	shell->history = new_history_list(shell->options->env);
	if (fd > 0)
	{
		close(fd);
		return (0);
	}
	return (ft_fdprintf(2, "history file error\n"));
}

static void	hist_del_one(t_shell *shell, t_history *h)
{
	if (h == shell->history && shell->history->head.next)
		shell->history = GET_NODE(((h)->head.next), t_history, head);
	else if (h == shell->history)
		shell->history = NULL;
	list_pop_one(&h->head);
	ft_strdel(&h->key);
	ft_strdel(&h->value);
	ft_memdel((void *)&h);
}

int			builtin_history(t_shell *shell, char **tab_arg)
{
	t_history	*h;
	int			i;
	int			flag;

	i = 0;
	h = shell->history;
	if ((flag = read_argv_hist(tab_arg, &i)) == _FLAG_C)
		return (trunc_hist(shell));
	if (flag == _FLAG_D)
	{
		if ((size_t)i > list_len(&h->head) || i <= 0)
			return (ft_fdprintf(2, "history: %d position out of range\n", i));
		while (--i > 0)
			h = GET_NODE(((h)->head.next), t_history, head);
		hist_del_one(shell, h);
	}
	else
		builtin_history_print(tab_arg, h, i);
	return (0);
}
