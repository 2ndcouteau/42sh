/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_save_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/19 20:55:19 by qrosa             #+#    #+#             */
/*   Updated: 2017/02/22 16:50:36 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opt_parse_arg.h"

static void	free_tab(t_opt **e)
{
	int		a;

	a = 0;
	while (a < (*e)->nb_arg)
	{
		if ((*e)->s_arg[a] != NULL)
			free((*e)->s_arg[a]);
		(*e)->s_arg[a] = NULL;
		a++;
	}
	free((*e)->s_arg);
	(*e)->s_arg = NULL;
}

static void	add_new_arg(char *str, t_opt **e)
{
	char	**new;
	int		i;

	i = 0;
	if ((new = (char**)malloc(sizeof(char*) * ((*e)->nb_arg + 2))))
	{
		while (i < (*e)->nb_arg)
		{
			new[i] = ft_strdup((*e)->s_arg[i]);
			i++;
		}
		(*e)->nb_arg += 1;
		new[i] = ft_strdup(str);
		new[i + 1] = NULL;
	}
	else
		(*e)->error = ERROR_MALLOC;
	free_tab(e);
	(*e)->s_arg = new;
	new = NULL;
}

static void	init_arg(char *str, t_opt **e)
{
	if (((*e)->s_arg = (char**)malloc(sizeof(char*) * 2)))
	{
		(*e)->s_arg[0] = ft_strdup(str);
		(*e)->s_arg[1] = NULL;
		(*e)->nb_arg = 1;
	}
	else
		(*e)->error = ERROR_MALLOC;
}

void		opt_save_arg(char *str, t_opt **e)
{
	if ((*e)->s_arg == NULL)
		init_arg(str, e);
	else
		add_new_arg(str, e);
}
