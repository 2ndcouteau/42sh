/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/02/23 14:45:13 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	readcmd(char *cmd, t_shell *sh, char *tmppath, char **pathcmp)
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
		ft_fdprintf(g_debug[1], "\033[31mread_cmd__");
	if (g_debug[0])
		ft_fdprintf(g_debug[1], "cmd = %s", cmd);
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

void test(int i)
{
	ft_fdprintf(2, " catch! sig %s\n", (i == SIGTTOU) ? "SIGTTOU" : "SIGTTIN");
	if (i == SIGTTOU)
	{
		if (tcsetpgrp(0, getpid()) == -1)
			ft_fdprintf(2, "tcsetpgrp(0, %d) == error\n", getpid());//a virer
	}
	signal(i, test);
}

void		exec_dad(t_jobs **jobs, t_shell *sh, t_processes *proc, int fd[4])
{
	t_processes *nxt;

	(!(*jobs)->pgid) ? (*jobs)->pgid = proc->pid : 1;
	if (setpgid(proc->pid, (*jobs)->pgid) == -1)
		ft_fdprintf(2, "\nsetpgid(proc->pid,proc->pid)ERROR\n");
	if (!sh->script && tcgetpgrp(1) != (*jobs)->pgid && ft_fdprintf(2, "tcgetpgrp(0) == {%d}; tcgetpgrp(1) == {%d}\n", tcgetpgrp(0), tcgetpgrp(1)))
	{
		if (tcsetpgrp(0, (*jobs)->pgid) == -1 && tcsetpgrp(1, (*jobs)->pgid) == -1)
			ft_fdprintf(2, "tcsetpgrp(0, proc->pid = {%d} pgid = %d, getpid={%d} getppid={%d}) ERROR\n", proc->pid, (*jobs)->pgid, getpid(), getppid());
	else
		ft_fdprintf(2, "tcsetpgrp(0, proc->pid = {%d} pgid = %d, getpid={%d} getppid={%d}) ok\n", proc->pid, (*jobs)->pgid, getpid(), getppid());
	}
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

static void	ft_execcmderr(t_shell **sh, t_processes *proc, char **tab_env)
{
	struct stat cmdstat;

	if (((stat(proc->path, &cmdstat)) < 0))
		ft_fdprintf(2, "42sh: \033[31mCommand not found: \033[0m%s\n"
		, proc->cmds->argv[0]);
	else if (!(cmdstat.st_mode & S_IXGRP)
	|| !(cmdstat.st_mode & S_IXOTH) || !(cmdstat.st_mode & S_IXUSR))
		ft_fdprintf(2, "42sh: \033[31mPermission denied: \033[0m%s\n"
		, proc->cmds->argv[0]);
	ft_stabdel(&tab_env);
	destroy_shell(sh);
}

static int	exec_child(t_jobs **jobs, t_shell *sh, t_processes *proc,
			t_dict *env)
{
	int		isbuiltin;
	int		test;
	char	**tab_env;

	if ((isbuiltin = ft_isbuiltin(*proc->cmds->argv)))
	{
		test = execbuiltin(sh, proc, isbuiltin);
		if (proc->head.next || proc->head.prev
		|| ((*jobs)->flags == ST_BG))
			exit(test);
		sh->status = test;
		proc->status = test;
		(*jobs)->status = test;
	}
	else
	{
		execve(proc->path, proc->cmds->argv, tab_env = dict2env(env));
		ft_execcmderr(&sh ,proc, tab_env);
		exit(1);
	}
	close_redir(GET_NODE(list_last(&proc->redir->head), t_redir, head));
	return (proc->status);
}

void		ft_execprocess(t_jobs **jobs, t_processes *p, t_shell *sh,
			t_dict *env)
{
	int			ret;
	int			isbuiltin;
	int			fd[4];

	(g_debug[0]) ? ft_fdprintf(g_debug[1], "Process: %s\n", *p->cmds->argv) : 1;
	if (!(isbuiltin = ft_isbuiltin(*p->cmds->argv)))
		readcmd(*p->cmds->argv, sh, ft_getenv(p->env, "PATH"), &p->path);
	if (isbuiltin == __BUILTIN_ENV && (builtin_env(jobs, p, sh) || 1))
		return ;
	if ((ret = 1) && p->head.next)
		if (creat_pipe(fd))
			return ;
	if (!(isbuiltin) || p->head.next || p->head.prev
	|| ((*jobs)->flags == ST_BG))
		if ((p->pid = fork()) == -1 && ft_putstr_fd("fork error\n", 2))
			return ;
	if (p->pid)
		exec_dad(jobs, sh, p, fd);
	else
	{
		if (!redir(p, fd))
			ret = exec_child(jobs, sh, p, env);
		if (!(isbuiltin) || p->head.next || p->head.prev)
			exit(ret);
	}
	ft_strdel(&p->path);
}
