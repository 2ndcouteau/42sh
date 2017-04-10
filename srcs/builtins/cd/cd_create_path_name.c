/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_create_path_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaosu <kaosu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 08:34:44 by kaosu             #+#    #+#             */
/*   Updated: 2017/04/07 22:18:09 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void		cd_read_argument(t_cmd *curr_cmd, t_dict *env,
					char **curr_pwd, char *new_path)
{
	int		cpt;

	cpt = cd_check_new_path(new_path);
	if (cpt < 2)
	{
		if (cpt == 0)
			cd_relative_path(curr_cmd, curr_pwd, new_path);
		else
			cd_absolute_path(curr_cmd, curr_pwd, new_path);
	}
	else
	{
		if (cpt == 2)
			cd_home(curr_cmd, env, curr_pwd, new_path + 1);
		else
			cd_oldpwd(curr_cmd, env, curr_pwd);
	}
}

static void		no_name(t_cmd *curr_cmd, t_dict *env, char **curr_pwd)
{
	char	*home_pwd;

	ft_bzero(*curr_pwd, PATH_MAX);
	if ((home_pwd = ft_getenv(env, "HOME")) != NULL)
	{
		*curr_pwd = ft_strncat(*curr_pwd, home_pwd, PATH_MAX);
		cd_check_valid_file(curr_cmd, curr_pwd, *curr_pwd);
	}
	else
		*curr_pwd = ft_strcpy(*curr_pwd, "/");
}

void			cd_create_path_name(t_cmd *curr_cmd,
					t_dict *env, t_opt **cd_opt, char **curr_pwd)
{
	if (ft_strlen(*curr_pwd) < (PATH_MAX - 1))
	{
		if ((*cd_opt)->nb_arg != 0)
			cd_read_argument(curr_cmd, env, curr_pwd, (*cd_opt)->s_arg[0]);
		else if (curr_cmd->size_split_line - (*cd_opt)->position != 0)
			cd_read_argument(curr_cmd, env, curr_pwd,
	curr_cmd->split_line[(*cd_opt)->position]);
		else
			no_name(curr_cmd, env, curr_pwd);
	}
	else
		cd_set_error(curr_cmd, "", 1);
}
