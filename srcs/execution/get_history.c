/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 06:39:47 by nboulaye          #+#    #+#             */
/*   Updated: 2017/02/20 16:30:44 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "history.h"

void	get_prev_hist(t_shell *sh, t_history **current)
{
	if (!(*current))
	{
		(*current) = GET_NODE(list_last(&sh->history->head), t_history, head);
		if (!(*current)->value && (*current)->head.prev)
			(*current) = GET_NODE(((*current)->head.prev), t_history, head);
	}
	else if ((*current)->head.prev)
		(*current) = GET_NODE(((*current)->head.prev), t_history, head);
}

void	get_next_hist(t_history **current)
{
	if (!(*current))
		return ;
	if ((*current)->head.next)
		(*current) = GET_NODE(((*current)->head.next), t_history, head);
	else
		(*current) = NULL;
}

char	*get_history(t_shell *sh, char *buf, int pos, char c)
{
	static t_history	*current = NULL;

	if ((!sh || !sh->history || !sh->history->value || !sh->history->key)
	&& !(current = NULL))
		return (NULL);
	if (c == 0)
	{
		get_prev_hist(sh, &current);
		while (current && current->head.prev
		&& !ft_strnequ(current->value, buf, pos))
			get_prev_hist(sh, &current);
	}
	else if (c == 1)
	{
		if (!current)
			return (NULL);
		get_next_hist(&current);
		while (current && current->head.next
			&& !ft_strnequ(current->value, buf, pos))
			get_next_hist(&current);
	}
	else if (c == -1)
		current = NULL;
	return (current && current->value) ? current->value : NULL;
}
