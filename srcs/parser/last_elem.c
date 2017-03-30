/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_elem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 18:00:01 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/20 21:30:35 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_jobs		*get_last_job(t_jobs *job)
{
	t_head	*head;

	if (job == NULL)
		return (NULL);
	head = list_last(&(job->head));
	return (GET_NODE(head, t_jobs, head));
}

t_processes	*get_last_process(t_processes *proc)
{
	t_head	*head;

	if (proc == NULL)
		return (NULL);
	head = list_last(&(proc->head));
	return (GET_NODE(head, t_processes, head));
}

t_cmds		*get_last_cmd(t_cmds *cmd)
{
	t_head	*head;

	if (cmd == NULL)
		return (NULL);
	head = list_last(&(cmd->head));
	return (GET_NODE(head, t_cmds, head));
}
