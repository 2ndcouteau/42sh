/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 15:58:17 by ljohan            #+#    #+#             */
/*   Updated: 2017/04/12 17:10:59 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		debug_jobs(t_jobs *j)
{
	int		i;
	t_jobs	*ptr;

	ft_putendl_fd("\n=== JOBS DEBUG ===", g_debug[1]);
	if (j == NULL)
		ft_putstr_fd("Null", g_debug[1]);
	else
	{
		i = 0;
		ptr = j;
		while (ptr != NULL)
		{
			ft_putstr_fd("j ", g_debug[1]);
			ft_putnbr_fd(i++, g_debug[1]);
			ft_putchar_fd('\n', g_debug[1]);
			debug_process(ptr->process);
			debug_flags(ptr->flags);
			ptr = (ptr->head.next) ? \
				GET_NODE(ptr->head.next, t_jobs, head) : NULL;
		}
	}
	ft_putendl_fd("\n=== END ===", g_debug[1]);
}

void		debug_parser(t_parser *parser)
{
	int		i;

	i = -1;
	ft_fdprintf(g_debug[1], "\norig: %s\n", parser->orig != NULL ? \
		parser->orig : "Null");
	ft_putstr_fd("      ", g_debug[1]);
	while (++i < parser->idx)
		ft_putchar_fd(' ', g_debug[1]);
	ft_putendl_fd("^", g_debug[1]);
	ft_fdprintf(g_debug[1], "part: %s\n", parser->part != NULL ? \
		parser->part : "Null");
	debug_states(parser->states);
	ft_putchar_fd('\n', g_debug[1]);
	debug_jobs(parser->jobs);
}
