/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 18:13:19 by qrosa             #+#    #+#             */
/*   Updated: 2017/02/23 17:24:49 by yoko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static const char *const g_cd_error[7] = {
	"",
	": cd: File name too long.",
	"cd: No such file or directory: ",
	"cd: Not a directory: ",
	"cd: Permission denied: ",
	"cd: OLDPWD is not set.",
	"cd: HOME is not set.",
};

void		cd_print_error(int error, char *name)
{
	if (error > 1 && error < 7)
	{
		ft_putstr_fd(g_cd_error[error], 2);
		ft_putendl_fd(name, 2);
	}
	else if (error <= 1)
	{
		ft_putstr_fd(name, 2);
		ft_putendl_fd(g_cd_error[error], 2);
	}
}
