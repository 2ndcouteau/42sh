/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_add_end_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 16:50:05 by qrosa             #+#    #+#             */
/*   Updated: 2017/02/22 20:11:30 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

bool		cd_add_end_path(char **current_pwd, char *add_elem, int pwd_len)
{
	int		cpt;

	cpt = 0;
	if (pwd_len + ft_strlen(add_elem) < PATH_MAX)
	{
		(*current_pwd)[pwd_len++] = '/';
		while (add_elem[cpt] != '\0')
		{
			(*current_pwd)[pwd_len] = add_elem[cpt];
			pwd_len++;
			cpt++;
		}
		(*current_pwd)[pwd_len] = '\0';
		return (SUCCESS);
	}
	return (ERROR);
}
