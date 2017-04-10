/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 16:19:13 by ljohan            #+#    #+#             */
/*   Updated: 2017/03/01 00:07:00 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	debug_redir(t_redir *red)
{
	t_redir	*ptr;

	ptr = red;
	if (g_debug[0])
		while (ptr != NULL)
		{
			ft_fdprintf(g_debug[1], "\nred:\n");
			ft_fdprintf(g_debug[1], "\tfdin: %s\n", ptr->fdin != NULL ?\
				ptr->fdin : "Null");
			ft_fdprintf(g_debug[1], "\trtype: %s\n",
				human_redtype(ptr->rtype));
			ft_fdprintf(g_debug[1], "\targ: %s\n",
				ptr->arg != NULL ? ptr->arg : "Null");
			ft_fdprintf(g_debug[1], "\theredoc: %s\n",
				ptr->heredoc != NULL ? ptr->heredoc : "Null");
			ft_fdprintf(g_debug[1], "\there_done: %s\n",
				ptr->heredoc_done == 0 ? "False" : "True");
			if (ptr->head.next == NULL)
				break ;
			ptr = GET_NODE(ptr->head.next, t_redir, head);
		}
}

int		try_redir_suite(t_shell *sh, t_parser *p, int *idx, t_redir *red)
{
	if ((red->rtype = get_rtype(p, idx)) == -1)
	{
		destroy_redir(&red);
		return (1);
	}
	else if (red->rtype == HEREDOC || red->rtype == REDAPPEND)
	{
		p->idx = *idx;
		red->arg = implicit_parse_one(sh, p);
		if (ft_strcmp(red->arg, "") == 0)
			ft_strdel(&(red->arg));
		if (red->rtype == HEREDOC)
			add_state(&(p->states), ST_HEREDOC);
	}
	else
	{
		if ((red->arg = get_red_fdout(p, idx)) == NULL)
		{
			p->idx = *idx;
			red->arg = implicit_parse_one(sh, p);
		}
	}
	return (0);
}

t_redir	*try_redir(t_shell *sh, t_parser *p)
{
	t_redir	*red;
	int		idx;

	if ((red = (t_redir*)ft_memalloc(sizeof(t_redir))) == NULL)
		return (NULL);
	idx = p->idx;
	red->fdin = get_left_redir(p, &idx);
	if (try_redir_suite(sh, p, &idx, red))
		return (NULL);
	if (red->arg == NULL || ft_strcmp(red->arg, "") == 0 ||
		ft_strcmp(red->arg, "&") == 0)
	{
		p->idx += forward_with(CURRENT(p), CS_BLANK) - CURRENT(p);
		if (*CURRENT(p) == 0)
			ft_fdprintf(2, "parse error: symbole inattendu: newline\n");
		else
			ft_fdprintf(2, "parse error: symbole inattendu: `%c'\n",
				*CURRENT(p));
		add_state(&(p->states), ST_ERR);
		destroy_redir(&red);
		return (NULL);
	}
	return (red);
}

void	push_redir(t_redir **red, t_redir *nred)
{
	if ((*red) == NULL)
		(*red) = nred;
	else
		list_append(&((*red)->head), &(nred->head));
}

void	merge_redir(t_parser *p, t_redir *red)
{
	t_processes *proc;

	if ((proc = get_last_process(get_last_job(p->jobs)->process)) == NULL)
		return ;
	push_redir(&(proc->redir), red);
}
