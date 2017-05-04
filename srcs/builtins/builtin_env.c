/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 11:10:25 by nboulaye          #+#    #+#             */
/*   Updated: 2017/04/26 20:43:40 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	env_forked(t_shell *sh, t_jobs **jobs, t_processes *proc
			, t_dict **modif_env)
{
	int		fd[4];

	if (proc->head.next)
		if (creat_pipe(fd))
			return (1);
	if ((proc->pid = fork()) == -1 && ft_putstr_fd("fork error\n", 2))
		return (1);
	if (proc->pid)
		exec_dad(jobs, sh, proc, fd);
	else
	{
		if (!redir(proc, fd) && modif_env && *modif_env)
			print_env(modif_env);
		else
			ft_fdprintf(2, "usage: env [-i] [-u name] [name=value ...]\n");
		exit(0);
	}
	destroy_dict(modif_env);
	return (0);
}

static void	maj_bins(t_shell *sh, t_dict *env)
{
	destroy_dict(&sh->options->bins);
	sh->options->bins = createbin_hashtab(ft_getenv(env, "PATH"));
}

static int	env_exec(t_shell *sh, t_jobs **jobs, t_processes *proc
			, t_dict **modif_env)
{
	int i;

	if (proc->head.next || ((*jobs)->flags == ST_BG))
	{
		i = env_forked(sh, jobs, proc, &(*modif_env));
		destroy_dict(&sh->options->bins);
		sh->options->bins =
			createbin_hashtab(ft_getenv(sh->options->env, "PATH"));
		return (i);
	}
	else
	{
		if (!(chk_redir(proc->redir)) && modif_env && *modif_env)
			print_env(&(*modif_env));
		else if (!modif_env || !*modif_env)
			ft_fdprintf(2, "usage: env [-i] [-u name] [name=value ...]\n");
		close_redir(GET_NODE(list_last(&proc->redir->head), t_redir, head));
	}
	maj_bins(sh, sh->options->env);
	return (0);
}

int			builtin_env(t_jobs **jobs, t_processes *proc, t_shell *sh)
{
	static t_dict	*modif_env = NULL;
	char			**old_arg;
	int				idx;
	int				r;

	idx = 1;
	r = 0;
	if (modif_env == NULL)
		modif_env = cpy_dict_env(proc->env);
	while (proc->cmds->argv[idx]
		&& (!(r = read_arg_env(proc, &idx, &modif_env, 0)) || r == -2))
		;
	maj_bins(sh, modif_env);
	if (r != 1 && proc->cmds->argv[idx] && (old_arg = proc->cmds->argv))
	{
		proc->cmds->argv = ft_stabdup(&(proc->cmds->argv[idx]));
		ft_stabdel(&old_arg);
		ft_execprocess(jobs, proc, sh, modif_env);
		destroy_dict(&modif_env);
		maj_bins(sh, sh->options->env);
		return (!(*jobs)) ? SIGTSTP :
		GET_NODE(list_last(&(*jobs)->process->head), t_processes, head)->status;
	}
	return (env_exec(sh, jobs, proc, &modif_env));
}
