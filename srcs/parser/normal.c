/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 16:56:34 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/28 19:18:25 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*parse_normal(t_parser *p)
{
	char	*part;
	char	*tmp;

	p->idx += forward_with(CURRENT(p), CS_BLANK) - CURRENT(p);
	tmp = FWD(CURRENT(p));
	part = ft_strsub(p->orig, p->idx, tmp - CURRENT(p));
	p->idx += tmp - CURRENT(p);
	return (part);
}

char		*handle_normal(t_shell *sh, t_parser *p)
{
	t_redir	*red;

	p->idx += forward_with(CURRENT(p), CS_BLANK) - CURRENT(p);
	if (p->first_word)
		return (handle_first_word(sh, p));
	if ((red = try_redir(sh, p)) != NULL)
	{
		debug_redir(red);
		merge_redir(p, red);
		return (NULL);
	}
	else
		return (parse_normal(p));
}

static void	transition_normal_suite2(t_parser *p)
{
	if (*CURRENT(p) == '`' && ++p->idx)
	{
		merge_part(p);
		push_state(&p->states, ST_SUBSHELL);
	}
	else
	{
		merge_part(p);
		push_state(&(p->states), ST_PIPE);
	}
}

static int	transition_normal_suite(t_parser *p)
{
	if (*CURRENT(p) == 0)
		push_state(&(p->states), ST_EOF);
	else if (*CURRENT(p) == '=')
	{
		update_part(p, ft_strdup("="));
		++p->idx;
	}
	else if (*CURRENT(p) == '"' && ++p->idx)
		push_state(&(p->states), ST_STR);
	else if (*CURRENT(p) == '\'' && ++p->idx)
		push_state(&(p->states), ST_QUOTE);
	else if (*CURRENT(p) == '$' && ++p->idx)
		push_state(&p->states, ST_VAR);
	else if (*CURRENT(p) == '&' && ++p->idx)
		push_state(&p->states, ST_BG);
	else if (*CURRENT(p) == '~')
		push_state(&p->states, ST_PATH);
	else if (*CURRENT(p) == '`' || *CURRENT(p) == '|')
		transition_normal_suite2(p);
	else
		return (0);
	return (1);
}

int			transition_normal(t_parser *p)
{
	char	ret;

	ret = 0;
	p->first_word = 0;
	if (transition_normal_suite(p))
		;
	else if (*CURRENT(p) == '>' || *CURRENT(p) == '<')
	{
		merge_part(p);
		push_state(&(p->states), ST_REDIR);
	}
	else if (*CURRENT(p) == '\\')
		push_state(&(p->states), ST_ESCAPE);
	else if (*CURRENT(p) == ';')
	{
		merge_part(p);
		push_state(&(p->states), ST_EOC);
	}
	else if (IS_BLANK(*CURRENT(p)))
		merge_part(p);
	else
		return ((ft_isprint(*CURRENT(p))) ? 0 : 1);
	return (ret);
}
