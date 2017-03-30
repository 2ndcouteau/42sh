/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_read_args.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 11:10:25 by nboulaye          #+#    #+#             */
/*   Updated: 2017/02/05 17:39:39 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char		chk_flag_env(char *argv)
{
	char flag;

	flag = 0;
	if (*argv == '-')
		while (*(++argv))
		{
			if (*argv == 'i')
				flag = _FLAG_I;
			else if (*argv == 'u')
				flag = _FLAG_U;
			else
				return (-1);
		}
	return (flag);
}

static int		destroy_dict_n_return(t_dict **env)
{
	destroy_dict(&(*env));
	return (1);
}

static int		env_flag_i(t_dict **modif_env, char **arg, int *idx)
{
	destroy_dict(&(*modif_env));
	if (!((*modif_env) = new_dict(_SIZE_ENV_DICT)))
		return (1);
	if (!arg[++(*idx)])
		return (-2);
	return (0);
}

int				read_arg_env(t_processes *proc, int *idx, t_dict **modif_env
					, int flag)
{
	char	*ptr;
	int		ret;

	if ((flag = chk_flag_env(proc->cmds->argv[*idx])) == _FLAG_U && ++(*idx))
	{
		if (proc->cmds->argv[(*idx)])
			ft_unsetenv((*modif_env), proc->cmds->argv[(*idx)++]);
		else
			return (destroy_dict_n_return(modif_env));
	}
	else if (flag == _FLAG_I)
	{
		if ((ret = env_flag_i(modif_env, proc->cmds->argv, idx)))
			return (ret);
	}
	else if (flag == -1)
		return (destroy_dict_n_return(modif_env));
	else if ((ptr = ft_strchr(proc->cmds->argv[(*idx)], '='))
	&& !(ptr[0] = '\0'))
		ft_setenv((*modif_env), proc->cmds->argv[(*idx)++], &(ptr[1]));
	else
		return (-1);
	return (0);
}
