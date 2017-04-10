/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_bg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/04/07 21:06:22 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void		print_debug(int status, int pid)
{
	if (g_debug[0])
	{
		ft_fdprintf(g_debug[1], "CHK wait BG :");
		ft_fdprintf(g_debug[1], "\033[94mAFTER BG End Wait_pid, pid = %d,\
		status = %d\033[0m\n", pid, status);
		ft_fdprintf(g_debug[1], "\033[94mAFTER BG WIFEXITED() = %d,\
		WIFSIGNALED() = %d,  WIFSTOPPED() = %d; \033[0m\n"
		, WIFEXITED(status), WIFSIGNALED(status), WIFSTOPPED(status));
		ft_fdprintf(g_debug[1], "\033[94mAFTER BG WEXITSTATUS() = %d,\
		WTERMSIG() = %d, WCOREDUMP() = %d WSTOPSIG() = %d; \033[0m\n"
		, WEXITSTATUS(status), WTERMSIG(status), WCOREDUMP(status)
		, WSTOPSIG(status));
	}
}

void		chk_status_bg(int status, t_jobs *jobs, t_jobs **jobs_lst)
{
	if (WIFEXITED(status))
	{
		if (!WEXITSTATUS(status))
			ft_fdprintf(1, "[%d]+ Done\t", jobs->id);
		else
			ft_fdprintf(1, "[%d]+\tExit %d\t", jobs->id, WEXITSTATUS(status));
		printarg(jobs->process, NULL, 1);
		del_stopped_jobs(jobs_lst, jobs->pgid);
	}
	else if (WIFSTOPPED(status))
	{
		if (WSTOPSIG(status) && (jobs->stat = _STOP_BG))
		{
			ft_fdprintf(1, "[%d]+\tStopped \t", jobs->id);
			printarg(jobs->process, NULL, 1);
		}
	}
	else if (WIFSIGNALED(status))
		if (WTERMSIG(status))
		{
			ft_fdprintf(1, "[%d]+\tExit %d\t", jobs->id, WTERMSIG(status));
			printarg(jobs->process, NULL, 1);
			del_stopped_jobs(jobs_lst, jobs->pgid);
		}
}

void		wait_bg(t_jobs **jobs_lst, t_jobs *jobs)
{
	int			pid;
	int			status;
	t_processes *proc;

	proc = jobs->process;
	status = 0;
	while (proc)
	{
		if ((pid = waitpid(proc->pid, &status,
			WUNTRACED | WNOHANG | WCONTINUED)) == 0)
			return ;
		proc = (proc->head.next) ?
		GET_NODE((proc->head.next), t_processes, head) : NULL;
	}
	print_debug(status, pid);
	jobs->status = status;
	jobs->process->status = status;
	chk_status_bg(status, jobs, jobs_lst);
}
