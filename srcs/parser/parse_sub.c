/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 14:06:14 by ljohan            #+#    #+#             */
/*   Updated: 2017/04/27 23:04:52 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_subshell	*last_subshell(t_processes *proc)
{
	if (!proc || !proc->subshell)
		return (NULL);
	return (GET_NODE(list_last(&(proc->subshell->head)), t_subshell, head));
}

static int			instring_subshell(t_parser *p, t_processes *proc)
{
	t_subshell		*sub;
	size_t			size;

	if ((sub = last_subshell(proc)) != NULL)
	{
		if (!sub->instring)
			itab_push(&sub->instring, p->part ? ft_strlen(p->part) : 0, -1);
		else
		{
			if ((size = itab_len(sub->instring)) > 0)
				size -= 1;
			if (sub->instring[size][0] == -1)
				sub->instring[size][0] = p->part ? ft_strlen(p->part) - 1 : 0;
			else if (sub->instring[size][1] == -1)
				sub->instring[size][1] = p->part ? ft_strlen(p->part) : 0;
			else
				itab_push(&sub->instring, p->part ? ft_strlen(p->part) : 0, -1);
		}
	}
	else
		return (-1);
	return (0);
}

static void			parse_subshell_suite(t_parser *p, t_processes *proc)
{
	t_subshell	*sub;

	if ((sub = last_subshell(proc)) == NULL)
	{
		add_subshell_idx(&(proc->subshell), (int)ft_stablen(proc->cmds->argv));
		sub = last_subshell(proc);
	}
	if (ft_stablen(proc->cmds->argv) != (size_t)sub->idx)
	{
		add_subshell_idx(&(proc->subshell), (int)ft_stablen(proc->cmds->argv));
		sub = last_subshell(proc);
	}
	if (GET_NODE(p->states->head.next, t_states, head)->state == ST_STR)
	{
		if (instring_subshell(p, proc) == -1)
			ft_fdprintf(2, "ERROR\n");
	}
}

char				*parse_subshell(t_parser *p)
{
	char		*part;
	char		*tmp;
	t_processes	*proc;

	p->idx += forward_with(CURRENT(p), CS_BLANK) - CURRENT(p);
	tmp = forward_escape(CURRENT(p), CS_SUBSHELL);
	part = ft_strsub(p->orig, p->idx, tmp - CURRENT(p));
	p->idx += tmp - CURRENT(p);
	if ((proc = get_last_process(get_last_job(p->jobs)->process)) == NULL)
		ft_fdprintf(2, "%sNull process error%s\n", F_RED, F_END);
	if (proc)
		parse_subshell_suite(p, proc);
	return (part);
}

int					transition_subshell(t_shell *shell, t_parser *p)
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
		if (STATE(p) == ST_STR)
			instring_subshell(p, proc);
		if (p->part && STATE(p) == ST_NORM)
			merge_part(p);
		return (0);
	}
	else if (!(*CURRENT(p)))
		push_state(&(p->states), ST_MULTILINE);
	else
		ft_fdprintf(2, "Parse Error ??\n");
	return (1);
}
