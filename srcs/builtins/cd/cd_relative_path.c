/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_relative_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 19:06:50 by qrosa             #+#    #+#             */
/*   Updated: 2017/04/07 22:23:32 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		cd_relative_path(t_cmd *current_cmd,
				char **current_pwd, char *new_path)
{
	int		new_path_len;
	int		pwd_len;

	pwd_len = ft_strlen(*current_pwd);
	new_path_len = ft_strlen(new_path);
	if ((new_path_len + pwd_len) > (PATH_MAX - 1))
		cd_set_error(current_cmd, new_path, 1);
	else
	{
		cd_add_end_path(current_pwd, new_path, pwd_len);
		cd_check_valid_file(current_cmd, current_pwd, new_path);
	}
}
