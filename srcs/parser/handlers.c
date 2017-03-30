/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:29:58 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/24 16:44:43 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	handle_eoc(t_parser *p)
{
	t_jobs	*j;

	j = get_new_job(&(p->jobs));
	j->process = new_processes();
	j->process->cmds = new_cmds();
	p->last_cmd = j->process->cmds;
	p->first_word = 1;
}

void	handle_error(t_parser *p)
{
	if (g_debug[0])
		ft_fdprintf(g_debug[1], "%shandle ERRROR\n%s", F_RED, F_END);
	(void)p;
}

void	handle_eof(t_parser *p)
{
	(void)p;
}

void	void_handler(t_parser *p)
{
	(void)p;
}
