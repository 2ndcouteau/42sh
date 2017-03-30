/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 12:16:50 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/20 19:12:13 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBS_H
# define JOBS_H

# include "list_head.h"
# include "processes.h"
# include "redir.h"

# define _RUN_FG		0
# define _RUN_BG		1
# define _STOP_BG		2

# define _FLAG_P		2
# define _FLAG_L		4

typedef struct		s_jobs
{
	t_head			head;
	t_processes		*process;
	pid_t			pgid;
	int				id;
	char			notified;
	int				flags;
	char			stat;
	int				status;
}					t_jobs;

t_jobs				*new_jobs(void);
void				destroy_jobs(t_jobs	**jobs);
t_jobs				*get_last_job(t_jobs *job);
t_jobs				*get_new_job(t_jobs **job);

#endif
