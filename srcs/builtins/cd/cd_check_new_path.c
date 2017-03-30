/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_check_new_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 18:52:28 by qrosa             #+#    #+#             */
/*   Updated: 2017/02/22 20:11:34 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			cd_check_new_path(char *new_path)
{
	if (new_path[0] == '-' && new_path[1] == '\0')
		return (3);
	else if (new_path[0] == '~')
		return (2);
	else if (new_path[0] == '/')
		return (1);
	return (0);
}
