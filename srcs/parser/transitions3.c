/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transitions3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 16:15:51 by ljohan            #+#    #+#             */
/*   Updated: 2017/04/12 21:04:18 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		transition_and(t_parser *p)
{
	return (transition_eoc(p));
}

int		transition_escape(t_parser *p)
{
	if (IS_BLANK(*CURRENT(p)))
		merge_part(p);
	pop_state(&(p->states));
	return (0);
}

int		transition_redir(t_parser *p)
{
	t_redir *red;

	red = get_current_redir(p);
	debug_redir(red);
	merge_part(p);
	pop_state(&(p->states));
	return (0);
}

int		transition_bg(t_parser *p)
{
	merge_part(p);
	pop_state(&(p->states));
	return (0);
}
