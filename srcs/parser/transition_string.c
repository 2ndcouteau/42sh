/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 18:17:25 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/28 17:14:11 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		transition_string_suite(t_parser *p)
{
	if (*CURRENT(p) == '$' && (p->idx++ || 1))
	{
		push_state(&p->states, ST_VAR);
		return (0);
	}
	else if (*CURRENT(p) == '~')
	{
		push_state(&p->states, ST_PATH);
		return (0);
	}
	else if (*CURRENT(p) == '|')
	{
		merge_part(p);
		push_state(&(p->states), ST_PIPE);
		return (0);
	}
	else if (*CURRENT(p) == '`')
	{
		p->idx++;
		push_state(&p->states, ST_SUBSHELL);
		return (0);
	}
	else
		push_state(&(p->states), ST_ERR);
	return (1);
}

int		transition_string(t_parser *p)
{
	if (*CURRENT(p) == 0)
	{
		push_state(&(p->states), ST_MULTILINE);
		return (1);
	}
	else if (*CURRENT(p) == '\\')
	{
		push_state(&(p->states), ST_ESCAPE);
		return (0);
	}
	else if (*CURRENT(p) == '"')
	{
		pop_state(&(p->states));
		p->idx++;
		if (IS_BLANK(*CURRENT(p)))
			merge_part(p);
		return (0);
	}
	return (transition_string_suite(p));
}

int		transition_quote(t_parser *p)
{
	if (*CURRENT(p) == 0)
	{
		push_state(&(p->states), ST_MULTILINE);
		return (1);
	}
	else if (*CURRENT(p) == '\'')
	{
		pop_state(&(p->states));
		p->idx++;
		if (IS_BLANK(*CURRENT(p)))
			merge_part(p);
		return (0);
	}
	else
		push_state(&(p->states), ST_ERR);
	return (1);
}
