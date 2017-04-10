/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_home.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 18:16:56 by qrosa             #+#    #+#             */
/*   Updated: 2017/04/07 22:19:32 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		cd_home(t_cmd *current_cmd, t_dict *env,
					char **current_pwd, char *new_path)
{
	int		pwd_len;
	int		new_path_len;
	char	*tmp;

	if (new_path[0] == '/')
		new_path++;
	if ((tmp = ft_getenv(env, "HOME")) == NULL)
		cd_set_error(current_cmd, "", 6);
	else
	{
		pwd_len = ft_strlen(tmp);
		new_path_len = ft_strlen(new_path) - 1;
		if ((new_path_len + pwd_len) > (PATH_MAX - 1))
			cd_set_error(current_cmd, new_path, 1);
		else
		{
			ft_bzero(*current_pwd, PATH_MAX);
			ft_strncat(*current_pwd, tmp, PATH_MAX);
			cd_add_end_path(current_pwd, new_path, pwd_len);
			cd_check_valid_file(current_cmd, current_pwd, *current_pwd);
		}
		tmp = ft_free_line(&tmp);
	}
}
