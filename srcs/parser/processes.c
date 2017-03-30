/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:37:01 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/24 15:31:13 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		destroy_redir2(t_redir *red)
{
	if (red->head.next)
		destroy_redir2(GET_NODE((red->head.next), t_redir, head));
	ft_strdel(&red->fdin);
	ft_strdel(&red->arg);
	ft_strdel(&red->heredoc);
	free(red);
}

t_processes	*new_processes(void)
{
	t_processes *proc;

	proc = (t_processes*)ft_memalloc(sizeof(t_processes));
	ft_bzero(&(proc->head), sizeof(t_head));
	return (proc);
}

static void	del_process(t_head *head)
{
	t_processes	*ptr;

	ptr = GET_NODE(head, t_processes, head);
	if (ptr->redir != NULL)
		destroy_redir2(ptr->redir);
	destroy_cmds(&(ptr->cmds));
	if (ptr->subshell != NULL)
	{
		//ft_strdel(&(ptr->subshell->code));
		free(ptr->subshell);
	}
	free(ptr);
	ptr = NULL;
}

void		destroy_processes(t_processes **proc)
{
	if ((*proc) == NULL)
		return ;
	list_iter(&((*proc)->head), &del_process);
	(*proc) = NULL;
}
