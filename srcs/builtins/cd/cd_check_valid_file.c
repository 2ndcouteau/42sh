/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_check_valid_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 17:38:50 by qrosa             #+#    #+#             */
/*   Updated: 2017/02/22 20:46:36 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <unistd.h>
#include <sys/stat.h>

bool	cd_check_valid_file(t_cmd *current_cmd, char **current_pwd,
	char *name)
{
	struct stat	t_stat;
	char		check;

	if (lstat(*current_pwd, &t_stat) >= 0)
	{
		check = cd_check_typefile(t_stat.st_mode & S_IFMT);
		if (check == 'd' || check == 'l')
		{
			if (access(*current_pwd, X_OK) == 0)
				return (SUCCESS);
			else
				cd_set_error(current_cmd, name, 4);
		}
		else
			cd_set_error(current_cmd, name, 3);
	}
	else
		cd_set_error(current_cmd, name, 2);
	return (ERROR);
}
