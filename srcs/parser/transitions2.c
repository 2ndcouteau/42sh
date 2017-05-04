/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transitions2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 16:15:15 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/23 14:13:45 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		transition_path(t_parser *p)
{
	merge_part(p);
	pop_state(&(p->states));
	return (0);
}

int		transition_pipe(t_parser *p)
{
	char	*test;

	test = forward_with(CURRENT(p), CS_BLANK);
	pop_state(&(p->states));
	test = forward_with(CURRENT(p), CS_BLANK);
	if (*test == 0)
	{
		push_state(&(p->states), ST_ONELINE);
		return (1);
	}
	else if (IS_EOC(*test))
	{
		ft_fdprintf(2, "parse error");
		push_state(&(p->states), ST_ERR);
		return (1);
	}
	return (0);
}

int		transition_eoc(t_parser *p)
{
	p->idx++;
	pop_state(&(p->states));
	return (0);
}

int		transition_or(t_parser *p)
{
	return (transition_eoc(p));
}
