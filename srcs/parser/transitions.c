/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transitions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:09:48 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/28 23:43:40 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		transition_heredoc(t_parser *p)
{
	(void)p;
	return (1);
}

int		transition_error(t_parser *p)
{
	(void)p;
	if (g_debug[0])
		ft_fdprintf(g_debug[1], "%stransiton ERROR%s\n", F_RED, F_END);
	return (1);
}

int		transition_eof(t_parser *p)
{
	merge_part(p);
	return (1);
}

int		transition_var(t_parser *p)
{
	pop_state(&(p->states));
	if (STATE(p) == ST_NORM && IS_BLANK(*CURRENT(p)))
		merge_part(p);
	return (0);
}
