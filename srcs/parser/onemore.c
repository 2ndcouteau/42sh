/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onemore.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 18:51:05 by ljohan            #+#    #+#             */
/*   Updated: 2017/03/01 00:11:31 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*handle_onemore(t_shell *sh,t_parser *p)
{
	(void)sh;
	return (parse_normal(p));
}

char	*implicit_parse_one(t_shell *shell, t_parser *p)
{
	char	*ret;
	int		stop;

	ft_fdprintf(g_debug[1], "%sSTARTING IMPLICIT PARSING%s", F_YEL, F_END);
	stop = 0;
	ret = NULL;
	p->merge = 0;
	if (STATE(p) != ST_ONEMORE)
		push_state(&p->states, ST_ONEMORE);
	while (!stop)
	{
		debug_parser(p);
		action(shell);
		stop = transition(shell, p)
			|| (STATE(p) == ST_ONEMORE && (IS_BLANK(*CURRENT(p))));
	}
	ft_fdprintf(g_debug[1], "%sEND OF IMPLICIT PARSING%s", F_YEL, F_END);
	if (p->part)
	{
		ret = p->part;
		p->part = NULL;
	}
	p->merge = 1;
	if (STATE(p) == ST_ONEMORE)
		pop_state(&p->states);
	return (ret);
}

int		transition_onemore(t_parser *p)
{
	if (*CURRENT(p) == 0)
		pop_state(&p->states);
	else if (*CURRENT(p) == '"' && ++p->idx)
	{
		push_state(&(p->states), ST_STR);
		return (0);
	}
	else if (*CURRENT(p) == '\'' && ++p->idx)
	{
		push_state(&(p->states), ST_QUOTE);
		return (0);
	}
	else if (*CURRENT(p) == '$' && ++p->idx)
	{
		push_state(&p->states, ST_VAR);
		return (0);
	}
	else if (*CURRENT(p) == '&')
		pop_state(&p->states);
	else if (*CURRENT(p) == '~')
	{
		push_state(&p->states, ST_PATH);
		return (0);
	}
	else if (*CURRENT(p) == '`' && ++p->idx)
	{
		push_state(&p->states, ST_SUBSHELL);
		return (0);
	}
	else if (*CURRENT(p) == '|')
		pop_state(&p->states);
	else if (IS_BLANK(*CURRENT(p)))
		pop_state(&p->states);
	else if (*CURRENT(p) == ';')
		pop_state(&p->states);
	else if (*CURRENT(p) == '>' || *CURRENT(p) == '<')
		pop_state(&p->states);
	if (STATE(p) == ST_ONEMORE)
		pop_state(&p->states);
	return (1);
}
