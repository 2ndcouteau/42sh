/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 18:04:29 by ljohan            #+#    #+#             */
/*   Updated: 2017/04/14 17:18:04 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	heredoc_not_done(t_head *head, void *arg)
{
	t_redir	*red;

	(void)arg;
	red = GET_NODE(head, t_redir, head);
	return (red->rtype == HEREDOC && !red->heredoc_done);
}

t_redir		*get_current_redir(t_parser *p)
{
	t_processes	*proc;
	t_redir		*red;

	if ((proc = get_last_process(get_last_job(p->jobs)->process)) != NULL)
	{
		if ((red = proc->redir) != NULL)
		{
			red = GET_NODE(
				list_get_first(&(red->head), NULL, &heredoc_not_done),
				t_redir, head);
			return (red);
		}
	}
	return (NULL);
}
