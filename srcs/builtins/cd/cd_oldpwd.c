/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_oldpwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 16:47:04 by qrosa             #+#    #+#             */
/*   Updated: 2017/04/07 22:18:11 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		cd_oldpwd(t_cmd *current_cmd, t_dict *env, char **current_pwd)
{
	char *old_pwd;

	ft_bzero(*current_pwd, PATH_MAX);
	if ((old_pwd = ft_getenv(env, "OLDPWD")) == NULL)
		cd_set_error(current_cmd, "", 5);
	else
	{
		*current_pwd = ft_strncat(*current_pwd, old_pwd, PATH_MAX);
		cd_check_valid_file(current_cmd, current_pwd, *current_pwd);
	}
}
