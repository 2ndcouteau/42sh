/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/02/20 21:55:52 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void		reset_pgrp(int nu_sig)
{
	if (g_debug[0])
		ft_fdprintf(g_debug[1], "RESET PGRP WITH pid: %d\n", getpid());
	if (tcsetpgrp(1, getpid()) == -1)
		ft_fdprintf(2, "Tcsetpgrp(1, getpid() ERROR\n");
	signal(nu_sig, SIG_DFL);
}

int			wait_bg_jobs(t_jobs *bg_jobs, int pid)
{
	if ((waitpid(pid, &bg_jobs->status, WUNTRACED)) < 0)
		(ft_putstr_fd("\033[31mwaitpid() error\n\033[0m", 2));
	if (!WIFSTOPPED(bg_jobs->status))
	{
		if (bg_jobs->status && bg_jobs->status != 13 && bg_jobs->status != 2
		&& bg_jobs->status < 28)
		{
			ft_putstrnbr_fd("\t", bg_jobs->pgid, 2);
			chk_status(bg_jobs->status);
			ft_putstrstr_fd(*bg_jobs->process->cmds->argv, " ", 2);
			ft_putchar_fd('\n', 2);
		}
	}
	signal(SIGTTIN, reset_pgrp);
	signal(SIGTTOU, reset_pgrp);
	return (bg_jobs->status);
}

static int	wake_jobs(t_jobs *bg_jobs, t_jobs **bg_jobs_lst
			, t_processes *lst_proc, int ret)
{
	printarg(bg_jobs->process, NULL, 1);
	bg_jobs->stat = _RUN_FG;
	if (tcsetpgrp(1, bg_jobs->pgid) == -1)
	{
		ft_fdprintf(2, "tcsetpgrp(1, bg_jobs->pgid) ERROR\n");
		bg_jobs->stat = _STOP_BG;
		return (1);
	}
	killpg(bg_jobs->pgid, SIGCONT);
	ret = -1;
	lst_proc = GET_NODE(list_last(&bg_jobs->process->head), t_processes, head);
	while (lst_proc)
	{
		wait_bg_jobs(bg_jobs, lst_proc->pid);
		if (ret == -1)
			ret = bg_jobs->status;
		lst_proc = (lst_proc && lst_proc->head.prev) ?
		GET_NODE((lst_proc->head.prev), t_processes, head) : NULL;
	}
	if (!WIFSTOPPED(ret))
		del_stopped_jobs(bg_jobs_lst, bg_jobs->pgid);
	else
		bg_jobs->stat = _STOP_BG;
	return (WEXITSTATUS(ret));
}

int			get_idx_bg_jobs(char **argv, t_jobs **bg_jobs)
{
	int	max;
	int	idx_process;

	max = list_len(&(*bg_jobs)->head);
	idx_process = 0;
	if (**argv == '%' && (*argv + 1))
	{
		while (idx_process < max && ((int)ft_atoi(*argv + 1) != (*bg_jobs)->id)
		&& ++idx_process)
			(*bg_jobs) = GET_NODE(((*bg_jobs)->head.next), t_jobs, head);
	}
	else
		while (idx_process < max
		&& !ft_strequ(*argv, *(*bg_jobs)->process->cmds->argv)
		&& !((int)ft_atoi(*argv) == (*bg_jobs)->pgid) && ++idx_process)
			(*bg_jobs) = GET_NODE(((*bg_jobs)->head.next), t_jobs, head);
	if (g_debug[0])
		ft_fdprintf(g_debug[1], "\nBUILT IN FG  idx = %d\n", idx_process);
	return (idx_process);
}

int			builtin_fg(t_jobs **bg_jobs, char **argv)
{
	t_jobs			*bg_jobs_parser;

	if ((!bg_jobs || !*bg_jobs) && ft_fdprintf(2, "fg: no current job!\n"))
		return (0);
	bg_jobs_parser = *bg_jobs;
	if (g_debug[0])
		ft_fdprintf(g_debug[1], "\nBUILT IN FG   ");
	if (argv && ++argv && *argv)
	{
		if ((size_t)get_idx_bg_jobs(argv, &bg_jobs_parser)
		< list_len(&(*bg_jobs)->head))
			return (wake_jobs(bg_jobs_parser, bg_jobs, NULL, 0));
	}
	else
	{
		bg_jobs_parser = GET_NODE(list_last(&(*bg_jobs)->head), t_jobs, head);
		if (g_debug[0])
			ft_fdprintf(g_debug[1], "\nBUILT IN FG\n");
		return (wake_jobs(bg_jobs_parser, bg_jobs, NULL, 0));
	}
	if (argv && *argv)
		ft_fdprintf(2, "fg: %s no such job!\n", *argv);
	return (1);
}
