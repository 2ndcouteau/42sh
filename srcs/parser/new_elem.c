/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 18:01:00 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/20 21:02:13 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_jobs			*get_new_job(t_jobs **jobs)
{
	t_jobs	*j;
	t_jobs	*nj;

	if ((j = get_last_job((*jobs))) == NULL)
	{
		j = new_jobs();
		(*jobs) = j;
	}
	else
	{
		nj = new_jobs();
		list_append(&(j->head), &(nj->head));
		j = nj;
	}
	return (j);
}

t_processes		*get_new_process(t_processes **proc)
{
	t_processes	*p;
	t_processes	*np;

	if ((p = get_last_process((*proc))) == NULL)
	{
		p = new_processes();
		(*proc) = p;
	}
	else
	{
		np = new_processes();
		list_append(&(p->head), &(np->head));
		p = np;
	}
	return (p);
}
