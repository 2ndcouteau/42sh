/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/01/19 12:28:25 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_stopped_pgid(int pgid)
{
	if (g_debug[0])
		ft_fdprintf(g_debug[1], "\n\n\033[92msav_stopped_process(t_jobs *(*jo\
		bs), int stopped)(*jobs)->pgid = %d\n\033[0m", pgid);
}

void	sav_stopped_jobs(t_jobs **bg_jobs_lst, t_jobs **jobs, int stopped)
{
	t_jobs *bg_jobs;

	bg_jobs = (*jobs);
	(*jobs) = ((*jobs)->head.next) ?
	GET_NODE(((*jobs)->head.next), t_jobs, head) : NULL;
	list_pop_one(&(bg_jobs)->head);
	(bg_jobs)->head.next = NULL;
	if (*bg_jobs_lst && (bg_jobs->id =
	GET_NODE(list_last(&(*bg_jobs_lst)->head), t_jobs, head)->id + 1))
		list_append(&((*bg_jobs_lst)->head), &(bg_jobs->head));
	else if ((bg_jobs->id = 1))
		(*bg_jobs_lst) = bg_jobs;
	bg_jobs->status =
	GET_NODE(list_last(&bg_jobs->process->head), t_processes, head)->status;
	if (stopped && (bg_jobs->stat = _STOP_BG))
	{
		ft_printf("[%d]+ Stopped\t", bg_jobs->id);
		printarg((bg_jobs)->process, NULL, 1);
	}
	else if ((bg_jobs->stat = _RUN_BG))
		ft_fdprintf(1, "[%d]\t%d\n", bg_jobs->id, bg_jobs->pgid);
	print_stopped_pgid(bg_jobs->pgid);
}

void	del_stopped_jobs(t_jobs **bg_jobs_lst, pid_t pgid)
{
	t_jobs	*bg_jobs;

	if (g_debug[0])
		ft_fdprintf(g_debug[1], "\n\n\033[92mdel_stopped_process");
	if (!bg_jobs_lst)
		return ;
	bg_jobs = *bg_jobs_lst;
	while (bg_jobs && !(pgid == bg_jobs->pgid))
	{
		bg_jobs = (bg_jobs->head.next) ?
		GET_NODE((bg_jobs->head.next), t_jobs, head) : NULL;
	}
	if (bg_jobs)
	{
		if (bg_jobs == *bg_jobs_lst)
			*bg_jobs_lst = ((*bg_jobs_lst)->head.next) ?
				GET_NODE(((*bg_jobs_lst)->head.next), t_jobs, head) : NULL;
		list_pop_one(&bg_jobs->head);
		bg_jobs->stat = 0;
		destroy_jobs(&bg_jobs);
	}
}
