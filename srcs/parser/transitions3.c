/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transitions3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 16:15:51 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/23 12:33:25 by ljohan           ###   ########.fr       */
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

// int		transition_postpipe(t_parser *p)
// {
// 	int	ret;
//
// 	if ((p->part == NULL || ft_strcmp(p->part, "") == 0))
// 	{
// 		push_state(&(p->states), ST_ONELINE);
// 		return (1);
// 	}
// 	pop_state(&(p->states));
// 	if (*CURRENT(p) != '\\')
// 	{
// 		ft_printf("On En Est La\n");
// 		merge_part(p);
// 	}
// 	ret = transition_normal(p);
// 	return (ret);
// }
