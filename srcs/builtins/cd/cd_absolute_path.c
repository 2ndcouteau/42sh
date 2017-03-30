/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_absolute_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 19:07:23 by qrosa             #+#    #+#             */
/*   Updated: 2017/02/22 20:11:28 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	cd_absolute_path(t_cmd *current_cmd, char **current_pwd, char *new_path)
{
	int		new_path_len;

	new_path_len = ft_strlen(new_path);
	if (new_path_len > (PATH_MAX - 1))
		cd_set_error(current_cmd, new_path, 1);
	else
	{
		ft_bzero(*current_pwd, PATH_MAX);
		*current_pwd = ft_strncat(*current_pwd, new_path, new_path_len);
		cd_check_valid_file(current_cmd, current_pwd, new_path);
	}
}
