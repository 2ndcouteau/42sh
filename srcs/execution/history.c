/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 06:39:47 by nboulaye          #+#    #+#             */
/*   Updated: 2017/01/24 11:35:52 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "history.h"

t_history	*new_history_list(t_dict *env)
{
	t_history		*history;

	if (!(history = ft_memalloc(sizeof(t_history))))
		return (NULL);
	open_read_f_history(history, env);
	return (history);
}

static void	add_in_lst(char *line2, t_history *new_hist, t_history **history)
{
	creat_elem_hist(line2, new_hist);
	if (history && *history && (*history)->key)
		list_append(&((*history)->head), &(new_hist->head));
	else
	{
		if (*history)
			destroy_history(*history);
		*history = new_hist;
	}
	ft_strdel(&line2);
}

void		add_history(char *line, t_history **history)
{
	char		*timestmp;
	char		*line1;
	char		*line2;
	t_history	*new_hist;

	if (!line || !*line)
		return ((void)get_history(NULL, NULL, 0, -1));
	timestmp = ft_itoa(time(NULL));
	line1 = ft_strjoin(timestmp, ":");
	line2 = ft_strjoin(line1, line);
	if (!(new_hist = ft_memalloc(sizeof(t_history))))
		return ;
	add_in_lst(line2, new_hist, history);
	ft_strdel(&line1);
	ft_strdel(&timestmp);
	get_history(NULL, NULL, 0, -1);
}

void		destroy_history(t_history *hist)
{
	if (hist->head.next)
		destroy_history(GET_NODE((hist->head.next), t_history, head));
	ft_strdel(&hist->key);
	ft_strdel(&hist->value);
	free(hist);
}
