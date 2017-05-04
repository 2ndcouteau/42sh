/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 14:51:49 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/24 17:21:32 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_subshell	*new_subshell(int idx)
{
	t_subshell	*sub;

	if ((sub = (t_subshell*)ft_memalloc(sizeof(t_subshell))) == NULL)
		return (NULL);
	sub->idx = idx;
	sub->instring = NULL;
	return (sub);
}

int			add_subshell_idx(t_subshell **sub, int idx)
{
	t_subshell	*new;

	if ((new = new_subshell(idx)) != NULL)
	{
		if ((*sub) == NULL)
			(*sub) = new;
		else
			list_append(&((*sub)->head), &(new->head));
		return (0);
	}
	return (-1);
}
