/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_swap_pwd_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 16:54:36 by qrosa             #+#    #+#             */
/*   Updated: 2017/04/07 22:17:17 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	cpy_pwd(t_dict *env, char **current_pwd)
{
	char *pwd;

	pwd = ft_getenv(env, "PWD");
	if (pwd != NULL)
	{
		ft_setenv(env, "OLDPWD", pwd);
		ft_setenv(env, "PWD", *current_pwd);
	}
	else
	{
		ft_setenv(env, "PWD", *current_pwd);
	}
}

static void	set_and_cpy_pwd(t_dict *env, char **current_pwd)
{
	char *pwd;

	pwd = ft_getenv(env, "PWD");
	if (pwd != NULL)
	{
		ft_setenv(env, "OLDPWD", pwd);
		ft_setenv(env, "PWD", *current_pwd);
	}
	else
	{
		ft_setenv(env, "PWD", *current_pwd);
		ft_setenv(env, "OLDPWD", *current_pwd);
	}
}

void		cd_swap_pwd_env(t_dict *env, char **current_pwd,
																t_opt **cd_opt)
{
	if (opt_check_last_opt((*cd_opt)->opt_all, 'L', 'P') == 1)
	{
		ft_bzero(*current_pwd, PATH_MAX);
		getcwd(*current_pwd, PATH_MAX);
	}
	else
	{
		cd_clean_path(current_pwd);
	}
	if (ft_getenv(env, "OLDPWD") != NULL)
		cpy_pwd(env, current_pwd);
	else
		set_and_cpy_pwd(env, current_pwd);
}
