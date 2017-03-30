/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 14:06:14 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/24 15:31:16 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*parse_subshell(t_parser *p)
{
	char	*part;
	char	*tmp;

	tmp = forward_escape(CURRENT(p), CS_SUBSHELL);
	part = ft_strsub(p->orig, p->idx, tmp - CURRENT(p));
	p->idx += tmp - CURRENT(p);
	return (part);
}

int		transition_subshell(t_shell *shell, t_parser *p)
{
	t_processes	*proc;

	(void)shell;
	if (*CURRENT(p) == '\\')
	{
		push_state(&(p->states), ST_ESCAPE);
		return (0);
	}
	else if (*CURRENT(p) == '`' && ++p->idx)
	{
		pop_state(&(p->states));
		if ((proc = get_last_process(get_last_job(p->jobs)->process)) == NULL)
			return (1);
		if (proc->cmds->argv == NULL)
		{
			if (p->part != NULL)
				proc->subshell = new_subshell(0);
		}
		else if (p->part != NULL)
			proc->subshell = new_subshell((int)ft_stablen(proc->cmds->argv));
		if (p->part)
			merge_part(p);
		return (0);
	}
	return (0);
}
