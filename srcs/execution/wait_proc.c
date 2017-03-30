/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/02/05 18:16:57 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void		print_wait_pid_debug(int pid, int status, char *name, char i)
{
	if (i)
		ft_fdprintf(g_debug[1],
		"\033[31mwaitprocess :%s, pid = %d\n\033[0m", name, pid);
	else
	{
		ft_fdprintf(g_debug[1], "\033[93mEnd Wait_pid, status = %d\
		, PID = {%d} ARG = %s; \033[0m\n", status, pid, name);
		ft_fdprintf(g_debug[1], "\033[93mWIFEXITED(status) = %d,\
		WIFSIGNALED(status) = %d,  WIFSTOPPED(status) = %d; \033[0m\n",
		WIFEXITED(status), WIFSIGNALED(status), WIFSTOPPED(status));
		ft_fdprintf(g_debug[1], "\033[93mWEXITSTATUS(status) = %d,\
		WTERMSIG(status) = %d, WCOREDUMP(status) = %d WSTOPSIG(status) = %d;\
		\033[0m\n", WEXITSTATUS(status), WTERMSIG(status), WCOREDUMP(status),
		WSTOPSIG(status));
	}
}

void		ft_void(void)
{
	return ;
}

void		wait_process(t_processes *proc, t_jobs **jobs, t_jobs **bg_jobs
				, t_shell *sh)
{
	if (g_debug[0])
		print_wait_pid_debug(proc->pid, sh->status, *proc->cmds->argv, 1);
	if (*jobs && (*jobs)->flags == ST_BG)
		return ((proc->pid == (*jobs)->pgid)) ?
		(sav_stopped_jobs(bg_jobs, jobs, 0)) : ft_void();
	if (((waitpid(proc->pid, &sh->status, WUNTRACED)) < 0)
	&& ft_fdprintf(2, "\033[31mwaitpid error: %s\n\033[0m", *proc->cmds->argv))
		exit(1);
	if (proc->pid == (*jobs)->pgid && WIFSTOPPED(sh->status)
	&& (WEXITSTATUS(sh->status) == SIGTSTP
		|| WEXITSTATUS(sh->status) == SIGSTOP))
		sav_stopped_jobs(bg_jobs, jobs, 1);
	else if (sh->status && sh->status != 13 && sh->status != 2
	&& sh->status < 28)
	{
		ft_putstrnbr_fd("\t", proc->pid, 2);
		chk_status(sh->status);
		printarg(proc, NULL, 1);
	}
	if (g_debug[0])
		print_wait_pid_debug(proc->pid, sh->status, *proc->cmds->argv, 0);
}
