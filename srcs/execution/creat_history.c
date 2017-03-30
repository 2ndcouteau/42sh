/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 06:39:47 by nboulaye          #+#    #+#             */
/*   Updated: 2017/01/22 19:43:48 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "history.h"

int			strchr_replace(char *str, char c_old, char c_new)
{
	if (str)
		while (*str)
		{
			if (*str == c_old)
				*str = c_new;
			str++;
		}
	return (1);
}

int			creat_elem_hist(char *line, t_history *history)
{
	char		*ptr;

	if (!(ptr = ft_strchr(line, ':')))
		return (0);
	if (!(history->key = ft_strndup(line, ptr - line)))
		return (0);
	if (!(history->value = ft_strdup(ptr + 1)))
		return (0);
	return (1);
}

int			open_read_f(t_dict *env)
{
	char	*home;
	char	*name;
	int		fd;

	name = NULL;
	fd = -1;
	if ((home = ft_getenv(env, "HOME")) && *home)
		name = ft_strjoin(home, "/.42sh_history");
	if (name)
		fd = open(name, O_RDONLY | O_CREAT
		, S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR);
	if (!name || fd == -1)
		fd = open("/tmp/.42sh_history", O_RDONLY | O_CREAT
		, S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR);
	if (name)
		ft_strdel(&name);
	return (fd);
}

int			print_hist_error(char **line)
{
	ft_fdprintf(2, "history file error\n");
	ft_strdel(line);
	return (0);
}

int			open_read_f_history(t_history *history, t_dict *env)
{
	int			fd;
	char		*line;
	t_history	*next;

	fd = open_read_f(env);
	if (get_next_line(fd, &line) > 0 && strchr_replace(line, 26, '\n'))
	{
		if (line && !(creat_elem_hist(line, history)))
			return (print_hist_error(&line));
		ft_strdel(&line);
		while (get_next_line(fd, &line) > 0 && strchr_replace(line, 26, '\n'))
		{
			if ((!(next = ft_memalloc(sizeof(t_history))))
			|| (line && !(creat_elem_hist(line, next))))
				return (print_hist_error(&line));
			list_append(&(history->head), &(next->head));
			history = GET_NODE((history->head.next), t_history, head);
			ft_strdel(&line);
		}
	}
	if (fd > 0)
		close(fd);
	if (line)
		ft_strdel(&line);
	return (1);
}
