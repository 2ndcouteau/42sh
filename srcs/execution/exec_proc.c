/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/04/27 21:28:17 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
	else if (ft_isdir(proc->path) > 0)
		ft_fdprintf(2, "42sh: \033[31m:%s is a directory\033[0m\n"
		, proc->cmds->argv[0]);
	ft_stabdel(&tab_env);
	destroy_shell(sh);
}

static int	exec_child(t_jobs **jobs, t_shell *sh, t_processes *proc,
			t_dict *env)
{
	int		isbuiltin;
	int		ret_builtin;
	char	**tab_env;

	if ((isbuiltin = ft_isbuiltin(*proc->cmds->argv)))
	{
		ret_builtin = execbuiltin(sh, proc, isbuiltin);
		if (proc->head.next || proc->head.prev
		|| ((*jobs)->flags == ST_BG))
			exit(ret_builtin);
		sh->status = ret_builtin;
		proc->status = ret_builtin;
		(*jobs)->status = ret_builtin;
	}
	else
	{
		execve(proc->path, proc->cmds->argv, tab_env = dict2env(env));
		ft_execcmderr(&sh, proc, tab_env);
		exit(1);
	}
	close_redir(GET_NODE(list_last(&proc->redir->head), t_redir, head));
	return (proc->status);
}

static int	execproc_suite(t_jobs **jobs, t_processes *p, t_shell *sh
				, t_dict *env)
{
	int	isbuiltin;

	if (!(isbuiltin = ft_isbuiltin(*p->cmds->argv)))
		readcmd(*p->cmds->argv, sh, ft_getenv(env, "PATH"), &p->path);
	if (isbuiltin == __BUILTIN_ENV && (builtin_env(jobs, p, sh) || 1))
		return (-1);
	return (isbuiltin);
}

static int	execproc_fork(t_jobs **jobs, t_processes *p, int isbuiltin)
{
	if (!(isbuiltin) || p->head.next || p->head.prev
		|| ((*jobs)->flags == ST_BG))
		if ((p->pid = fork()) == -1 && ft_putstr_fd("fork error\n", 2))
			return (1);
	return (0);
}

void		ft_execprocess(t_jobs **jobs, t_processes *p, t_shell *sh,
			t_dict *env)
{
	int			ret;
	int			isbuiltin;
	int			fd[4];

	if (p->subshell != NULL)
		replace_subshells(sh, &p);
	if (p && p->cmds && p->cmds->argv && p->cmds->argv[0])
	{
		if ((isbuiltin = execproc_suite(jobs, p, sh, env)) == -1)
			return ;
		if ((ret = 1) && p->head.next && creat_pipe(fd))
			return ;
		if (execproc_fork(jobs, p, isbuiltin))
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
}
