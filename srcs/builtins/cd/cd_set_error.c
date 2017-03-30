/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_set_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 16:53:00 by qrosa             #+#    #+#             */
/*   Updated: 2017/02/22 20:12:12 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		cd_set_error(t_cmd *current_cmd, char *name, int nbr)
{
	current_cmd->error_name = ft_strdup(name);
	current_cmd->error_nbr = nbr;
}
