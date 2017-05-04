/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/04/27 23:33:18 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		check_varname_format(char *varname)
{
	if (ft_isdigit(*varname))
		return (0);
	while (*varname)
	{
		if (!(ft_isalnum(*varname) || *varname == '_') || *varname == '=')
			return (0);
		varname++;
	}
	return (1);
}

int		builtin_setenv(t_processes *proc, t_shell *sh)
{
	int ret;

	if (!proc->cmds->argv[1] || (proc->cmds->argv[2] && proc->cmds->argv[3]))
	{
		ft_fdprintf(2, "format `setenv key [value]`\n");
		return (1);
	}
	if (!check_varname_format(proc->cmds->argv[1]))
	{
		ft_fdprintf(2, "setenv: bad varname format\n");
		return (1);
	}
	if (proc->cmds->argv[2])
	{
		ret = ft_setenv(proc->env, proc->cmds->argv[1], proc->cmds->argv[2]);
		if (ft_strequ(proc->cmds->argv[1], "PATH"))
		{
			destroy_dict(&sh->options->bins);
			sh->options->bins = createbin_hashtab(ft_getenv(proc->env, "PATH"));
		}
		return (ret);
	}
	else
		return (ft_setenv(proc->env, proc->cmds->argv[1], NULL));
}

t_dict	*print_env(t_dict **env)
{
	char	**t;
	ssize_t	idx;

	if (!env)
		return (NULL);
	t = dict2env(*env);
	idx = -1;
	while (t && t[++idx])
		ft_putendl(t[idx]);
	ft_stabdel(&t);
	destroy_dict(env);
	*env = NULL;
	return (NULL);
}

int		builtin_unsetenv(t_processes *proc, t_shell *sh)
{
	int	idx;
	int	ret;

	idx = 0;
	ret = 0;
	if (!proc->cmds->argv[1])
	{
		ft_fdprintf(2, "format `unsetenv [key ...]`");
		return (1);
	}
	while (proc->cmds->argv[++idx])
	{
		if (ft_strequ(proc->cmds->argv[idx], "PATH"))
		{
			destroy_dict(&sh->options->bins);
			sh->options->bins = new_dict(128);
		}
		if ((ret = ft_unsetenv(proc->env, proc->cmds->argv[idx])) != 0)
			break ;
	}
	return (ret);
}
