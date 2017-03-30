/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/01/29 00:51:50 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void		print_debug_bg_jobs(int pgid, int status)
{
	if (g_debug[0])
	{
		ft_fdprintf(g_debug[1], "\033[94mAFTER BG End Wait_pid, pid = %d,\
		status = %d\033[0m\n", pgid, status);
		ft_fdprintf(g_debug[1], "\033[94mAFTER BG WIFEXITED() = %d,\
		WIFSIGNALED() = %d,  WIFSTOPPED() = %d; \033[0m\n",
		WIFEXITED(status), WIFSIGNALED(status),
		WIFSTOPPED(status));
		ft_fdprintf(g_debug[1], "\033[94mAFTER BG WEXITSTATUS() = %d\
		WTERMSIG() = %d, WCOREDUMP() = %d WSTOPSIG() = %d; \033[0m\n",
		WEXITSTATUS(status), WTERMSIG(status)
		, WCOREDUMP(status), WSTOPSIG(status));
	}
}

static int	wake_jobs(t_jobs *bg_jobs, t_jobs **bg_jobs_lst)
{
	(void)bg_jobs_lst;
	if (g_debug[0])
		ft_fdprintf(g_debug[1], "Sigcont for : {%d}\n", bg_jobs->pgid);
	killpg(bg_jobs->pgid, SIGCONT);
	print_debug_bg_jobs(bg_jobs->pgid, bg_jobs->status);
	bg_jobs->stat = _RUN_BG;
	if (WIFEXITED(bg_jobs->status))
	{
		ft_fdprintf(2, "bg: job has terminated\n");
		return (1);
	}
	else
		printarg(bg_jobs->process, "&", 1);
	ft_fdprintf(g_debug[1], "\nBUILTIN BG FIRST bg_jobs->pgid{%d}\n"
	, bg_jobs->pgid);
	return (0);
}

int			builtin_bg(t_jobs **bg_jobs, char **argv)
{
	t_jobs			*bg_jobs_parser;

	if ((!bg_jobs || !*bg_jobs) && ft_fdprintf(2, "bg: no current job!\n"))
		return (1);
	bg_jobs_parser = *bg_jobs;
	if (g_debug[0])
		ft_fdprintf(g_debug[1], "\nBUILT IN BG   ");
	if (argv && ++argv && *argv)
	{
		if ((size_t)get_idx_bg_jobs(argv, &bg_jobs_parser)
		< list_len(&(*bg_jobs)->head))
			return (wake_jobs(bg_jobs_parser, bg_jobs));
	}
	else
	{
		if ((bg_jobs_parser = GET_NODE(list_last(&(*bg_jobs)->head)
		, t_jobs, head)))
			return (wake_jobs(bg_jobs_parser, bg_jobs));
	}
	if (argv && *argv)
		ft_fdprintf(2, "bg: %s no such job!\n", *argv);
	return (1);
}
