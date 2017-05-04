/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:37:28 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/20 16:53:04 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_jobs		*new_jobs(void)
{
	t_jobs	*jobs;

	jobs = (t_jobs*)ft_memalloc(sizeof(t_jobs));
	return (jobs);
}

static void	del_job(t_head *head)
{
	t_jobs	*ptr;

	ptr = GET_NODE(head, t_jobs, head);
	if (!ptr->stat)
	{
		destroy_processes(&(ptr->process));
		ft_bzero((void*)&(ptr->head), sizeof(t_head));
		ft_memdel((void **)&ptr);
	}
	ptr = NULL;
}

void		destroy_jobs(t_jobs **jobs)
{
	if ((*jobs) == NULL)
		return ;
	list_iter(&((*jobs)->head), &del_job);
	(*jobs) = NULL;
}
