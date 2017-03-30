/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_if_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/02/05 18:14:42 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		ft_isbuiltin2(char *name)
{
	if (ft_strequ(name, "echo"))
		return (__BUILTIN_ECHO);
	else if (ft_strequ(name, "alias"))
		return (__BUILTIN_ALIAS);
	else if (ft_strequ(name, "unalias"))
		return (__BUILTIN_UNALIAS);
	else if (ft_strequ(name, "set"))
		return (__BUILTIN_SET);
	else if (ft_strequ(name, "unset"))
		return (__BUILTIN_UNSET);
	else if (ft_strequ(name, "history"))
		return (__BUILTIN_HISTORY);
	return (0);
}

int		ft_isbuiltin(char *name)
{
	if (ft_strequ(name, "cd"))
		return (__BUILTIN_CD);
	else if (ft_strequ(name, "env"))
		return (__BUILTIN_ENV);
	else if (ft_strequ(name, "setenv"))
		return (__BUILTIN_SETENV);
	else if (ft_strequ(name, "unsetenv"))
		return (__BUILTIN_UNSETENV);
	else if (ft_strequ(name, "help"))
		return (__BUILTIN_HELP);
	else if (ft_strequ(name, "bg"))
		return (__BUILTIN_BG);
	else if (ft_strequ(name, "fg"))
		return (__BUILTIN_FG);
	else if (ft_strequ(name, "exit"))
		return (__BUILTIN_EXIT);
	else if (ft_strequ(name, "jobs"))
		return (__BUILTIN_JOBS);
	else
		return (ft_isbuiltin2(name));
}

int		execbuiltin2(t_shell *sh, t_processes *proc
		, int idx_builtin)
{
	if (idx_builtin == __BUILTIN_UNSETENV)
		return (builtin_unsetenv(proc, sh));
	else if (idx_builtin == __BUILTIN_ALIAS)
		return (builtin_alias(sh, proc->cmds->argv));
	else if (idx_builtin == __BUILTIN_UNALIAS)
		return (builtin_unalias(sh, proc->cmds->argv));
	else if (idx_builtin == __BUILTIN_SET)
		return (builtin_set(sh, proc->cmds->argv));
	else if (idx_builtin == __BUILTIN_UNSET)
		return (builtin_unset(sh, proc->cmds->argv));
	else if (idx_builtin == __BUILTIN_HISTORY)
		return (builtin_history(sh, proc->cmds->argv));
	return (1);
}

int		execbuiltin(t_shell *sh, t_processes *proc
		, int idx_builtin)
{
	if (idx_builtin == __BUILTIN_CD)
		return (ft_cd(proc->cmds->argv, proc->env));
	else if (idx_builtin == __BUILTIN_SETENV)
		return (builtin_setenv(proc, sh));
	else if (idx_builtin == __BUILTIN_HELP)
		return (ft_help(&(proc->cmds->argv[1])));
	else if (idx_builtin == __BUILTIN_EXIT)
		return (ft_exit(sh, proc));
	else if (idx_builtin == __BUILTIN_BG)
		return (builtin_bg(&sh->bg_jobs, proc->cmds->argv));
	else if (idx_builtin == __BUILTIN_FG)
		return (builtin_fg(&sh->bg_jobs, proc->cmds->argv));
	else if (idx_builtin == __BUILTIN_JOBS)
		return (builtin_jobs(&sh->bg_jobs, proc->cmds->argv));
	else if (idx_builtin == __BUILTIN_ECHO)
		return (builtin_echo(proc->cmds->argv));
	else
		return (execbuiltin2(sh, proc, idx_builtin));
}
