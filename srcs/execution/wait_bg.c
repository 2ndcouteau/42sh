/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_bg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/02/18 19:46:58 by nboulaye         ###   ########.fr       */
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

void		wait_all_grp(t_jobs *jobs, int pid, int status)
{
	t_processes	*lst_proc;

	lst_proc = GET_NODE(list_last(&jobs->process->head), t_processes, head);
	while (lst_proc)
	{
		if (pid != lst_proc->pid)
		{
			if (waitpid(lst_proc->pid, &lst_proc->status, WNOHANG) < 0)
				ft_fdprintf(2, "\033[31mwaitpid() error: %s\n\033[0m",
				*lst_proc->cmds->argv);
		}
		else
			lst_proc->status = status;
		lst_proc = (lst_proc && lst_proc->head.prev) ?
			GET_NODE((lst_proc->head.prev), t_processes, head) : NULL;
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
	int	pid;
	int	status;

	status = 0;
	if ((pid = waitpid(-jobs->pgid, &status,
		WUNTRACED | WNOHANG | WCONTINUED)) < 0)
	{
		ft_fdprintf(2, "\033[31mwaitpid() error: {%s}\n\033[0m",
			*jobs->process->cmds->argv);
		exit(1);//resturn ??
	}
	if (!pid)
		return ;
	print_debug(status, pid);
	wait_all_grp(jobs, pid, status);
	jobs->status = status;
	jobs->process->status = status;
	chk_status_bg(status, jobs, jobs_lst);
}
