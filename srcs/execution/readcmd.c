/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/04/12 17:34:02 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void		readcmd(char *cmd, t_shell *sh, char *tmppath, char **pathcmp)
{
	t_cell	*result;
	char	*tmp;
	char	*cmd_lower;

	if (ft_strnequ(cmd, "./", 2) || cmd[0] == '/')
	{
		*pathcmp = ft_strdup(cmd);
		return ;
	}
	tmppath = ft_strjoin("/", cmd);
	if (g_debug[0])
		ft_fdprintf(g_debug[1], "cmd = %s ", cmd);
	cmd_lower = ft_strtolower(cmd);
	if ((result = dict_get(sh->options->bins, cmd_lower)))
		tmp = result->value;
	else
		tmp = NULL;
	*pathcmp = (tmp) ? ft_strjoin(tmp, tmppath) : ft_strjoin(tmp, tmppath);
	free(tmppath);
	free(cmd_lower);
	if (g_debug[0])
		ft_fdprintf(g_debug[1], "pathcmp = %s\n\033[0m", *pathcmp);
}

static void	exec_dad_suite(t_jobs **jobs, t_shell *sh, t_processes *proc)
{
	if (!sh->script && tcgetpgrp(1) != (*jobs)->pgid)
	{
		if (g_debug[0])
			ft_fdprintf(g_debug[1],
				"tcgetpgrp(0) == {%d}; tcgetpgrp(1) == {%d}\n",
				tcgetpgrp(0), tcgetpgrp(1));
		if (tcsetpgrp(0, (*jobs)->pgid) == -1
			&& tcsetpgrp(1, (*jobs)->pgid) == -1)
			ft_fdprintf(2, "tcsetpgrp(0, proc->pid = {%d} pgid = %d,\n\
				getpid={%d} getppid={%d}) ERROR\n",
				proc->pid, (*jobs)->pgid, getpid(), getppid());
		else if (g_debug[0])
			ft_fdprintf(g_debug[1], "tcsetpgrp(0, proc->pid = {%d} pgid = %d,\n\
				getpid={%d} getppid={%d}) ok\n", proc->pid,
				(*jobs)->pgid, getpid(), getppid());
	}
}

void		exec_dad(t_jobs **jobs, t_shell *sh, t_processes *proc, int fd[4])
{
	t_processes *nxt;

	(!(*jobs)->pgid) ? (*jobs)->pgid = proc->pid : 1;
	if (setpgid(proc->pid, (*jobs)->pgid) == -1)
		ft_fdprintf(2, "\nsetpgid(proc->pid,proc->pid)ERROR\n");
	exec_dad_suite(jobs, sh, proc);
	if (proc->head.next)
	{
		if (g_debug[0])
			ft_fdprintf(g_debug[1], "exec_dad if (proc->head.next)\n");
		close(fd[3]);
		dup2(fd[2], STDIN_FILENO);
		nxt = GET_NODE((proc->head.next), t_processes, head);
		nxt->env = proc->env;
		ft_execprocess(jobs, nxt, sh, proc->env);
		dup2(fd[0], STDOUT_FILENO);
		dup2(fd[1], STDIN_FILENO);
		close(fd[2]);
		close(fd[1]);
		close(fd[0]);
	}
	wait_process(proc, jobs, &sh->bg_jobs, sh);
}
