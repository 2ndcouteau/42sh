/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_free_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 18:13:01 by qrosa             #+#    #+#             */
/*   Updated: 2017/02/22 16:50:18 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opt_parse_arg.h"

static void	free_s_arg(t_opt **e)
{
	int i;

	i = 0;
	if ((*e)->s_arg != NULL)
	{
		while ((*e)->s_arg[i] != NULL)
		{
			if ((*e)->s_arg[i] != NULL)
			{
				free((*e)->s_arg[i]);
				(*e)->s_arg[i] = NULL;
			}
			i++;
		}
		free((*e)->s_arg);
		(*e)->s_arg = NULL;
	}
}

void		opt_free(t_opt **e)
{
	if ((*e)->define != NULL)
		(*e)->define = ft_free_tab((*e)->define);
	(*e)->define = NULL;
	if ((*e)->opt != NULL)
		free((*e)->opt);
	(*e)->opt = NULL;
	if ((*e)->l_opt != NULL)
		free((*e)->l_opt);
	(*e)->l_opt = NULL;
	if ((*e)->opt_b != NULL)
		free((*e)->opt_b);
	(*e)->opt_b = NULL;
	if ((*e)->opt_all != NULL)
		free((*e)->opt_all);
	(*e)->opt_all = NULL;
	free_s_arg(e);
	if (*e != NULL)
		free(*e);
	*e = NULL;
}
