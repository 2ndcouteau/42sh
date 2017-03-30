/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_create_path_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaosu <kaosu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 08:34:44 by kaosu             #+#    #+#             */
/*   Updated: 2017/02/23 16:38:17 by yoko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	cd_read_argument(t_cmd *current_cmd, t_dict *env, char **current_pwd, char *new_path)
{
	int		cpt;

	cpt = cd_check_new_path(new_path);
	if (cpt < 2)
	{
		if (cpt == 0)
			cd_relative_path(current_cmd, current_pwd, new_path);
		else
			cd_absolute_path(current_cmd, current_pwd, new_path);
	}
	else
	{
		if (cpt == 2)
			cd_home(current_cmd, env, current_pwd, new_path + 1);
		else
			cd_oldpwd(current_cmd, env, current_pwd);
	}
}

static void	no_name(t_cmd *current_cmd, t_dict *env, char **current_pwd)
{
	char	*home_pwd;

	ft_bzero(*current_pwd, PATH_MAX);
	if ((home_pwd = ft_getenv(env, "HOME")) != NULL)
	{
		*current_pwd = ft_strncat(*current_pwd, home_pwd, PATH_MAX);
		cd_check_valid_file(current_cmd, current_pwd, *current_pwd);
	}
	else
		*current_pwd = ft_strcpy(*current_pwd, "/");
//	tmp = ft_free_line(&tmp);
}

void		cd_create_path_name(t_cmd *current_cmd, t_dict *env, t_opt **cd_opt, char **current_pwd)
{
	if (ft_strlen(*current_pwd) < (PATH_MAX - 1))
	{
		if ((*cd_opt)->nb_arg != 0)
			cd_read_argument(current_cmd, env, current_pwd, (*cd_opt)->s_arg[0]);
		else if (current_cmd->size_split_line - (*cd_opt)->position != 0)
			cd_read_argument(current_cmd, env, current_pwd,
	current_cmd->split_line[(*cd_opt)->position]);
		else
			no_name(current_cmd, env, current_pwd);
	}
	else
		cd_set_error(current_cmd, "", 1);
}
