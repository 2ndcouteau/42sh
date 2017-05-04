/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/04/27 18:53:31 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void		printarg(t_processes *proc, char *str, int fd)
{
	char **arg;

	while (proc)
	{
		arg = proc->cmds->argv;
		while (*arg)
			ft_fdprintf(fd, "%s ", *arg++);
		if (proc->head.next)
		{
			ft_fdprintf(fd, "| ");
			proc = GET_NODE((proc->head.next), t_processes, head);
		}
		else
			proc = NULL;
	}
	(str) ? ft_fdprintf(fd, "%s\n", str) : ft_putchar_fd('\n', fd);
}

char		chk_flag_jobs(char *argv)
{
	char flag;

	flag = 0;
	if (*argv == '-')
		while (*(++argv))
		{
			if (*argv == 'p')
				flag = _FLAG_P;
			if (*argv == 'l')
				flag = _FLAG_L;
		}
	return (flag);
}

void		print_jobs(char flag, t_jobs *bg_jobs_parser, t_jobs *last)
{
	if (flag & _FLAG_P)
		ft_printf("%d\n", bg_jobs_parser->pgid);
	else
	{
		ft_printf("[%d]", bg_jobs_parser->id);
		if (bg_jobs_parser == last)
			ft_printf("+");
		else if (last->head.prev
		&& bg_jobs_parser == GET_NODE(last->head.prev, t_jobs, head))
			ft_printf("-");
		else
			ft_printf(" ");
		ft_printf(" ");
		if (flag & _FLAG_L)
			ft_printf("%d", bg_jobs_parser->pgid);
		if (bg_jobs_parser->stat == _RUN_BG)
			ft_printf("\tRunning");
		else if (bg_jobs_parser->stat == _STOP_BG && ft_printf("\tStopped"))
			if (flag & _FLAG_L && WSTOPSIG(bg_jobs_parser->process->status))
				ft_printf(": %d", WSTOPSIG(bg_jobs_parser->process->status));
		ft_printf("\t");
		printarg(bg_jobs_parser->process, NULL, 1);
	}
}

int			builtin_jobs(t_jobs **bg_jobs, char **argv)
{
	int				idx_process;
	char			flag;
	t_jobs			*bg_jobs_parser;
	t_jobs			*last;

	flag = 1;
	while (++argv && *argv && flag)
	{
		flag = chk_flag_jobs(*argv);
		if (g_debug[0])
			ft_fdprintf(g_debug[1], "flag = %b, *arg = %s\n", flag, *argv);
	}
	idx_process = 0;
	if (!bg_jobs || !*bg_jobs)
		return (ft_fdprintf(2, "jobs: no current job!!\n"));
	bg_jobs_parser = *bg_jobs;
	last = GET_NODE(list_last(&(*bg_jobs)->head), t_jobs, head);
	while (bg_jobs_parser && ++idx_process)
	{
		print_jobs(flag, bg_jobs_parser, last);
		bg_jobs_parser = (bg_jobs_parser->head.next)
		? GET_NODE((bg_jobs_parser->head.next), t_jobs, head) : NULL;
	}
	return (!idx_process && ft_fdprintf(2, "jobs: no current job!\n")) ? 1 : 0;
}
