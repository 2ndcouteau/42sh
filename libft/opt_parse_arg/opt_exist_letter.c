/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_exist_letter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/19 20:55:19 by qrosa             #+#    #+#             */
/*   Updated: 2017/02/22 16:50:13 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opt_parse_arg.h"

static void	add_option_null(char c, t_opt **e)
{
	if (((*e)->opt = ft_memalloc(2)))
	{
		(*e)->opt[0] = c;
		(*e)->opt[1] = '\0';
		(*e)->mark = ALL_OK;
	}
}

static void	add_option(char c, t_opt **e, int i)
{
	char *new;

	if ((*e)->opt != NULL)
	{
		if ((new = ft_memalloc(ft_strlen((*e)->opt) + 2)))
		{
			while ((*e)->opt[i] != '\0')
			{
				new[i] = (*e)->opt[i];
				i++;
			}
			new[i] = c;
			new[i + 1] = '\0';
			free((*e)->opt);
			(*e)->opt = new;
			new = NULL;
		}
		else
		{
			(*e)->error = ERROR_MALLOC;
			(*e)->mark = BAD_OPT;
		}
	}
	else
		add_option_null(c, e);
}

static void	add_all_option(char *str, t_opt **e, int i)
{
	char	*new;
	char	*tmp;

	new = NULL;
	tmp = ft_memalloc(2);
	tmp[0] = str[i];
	tmp[1] = '\0';
	if ((*e)->opt_all == NULL)
	{
		(*e)->opt_all = tmp;
		tmp = NULL;
	}
	else
	{
		new = ft_strjoin((*e)->opt_all, tmp);
		free((*e)->opt_all);
		(*e)->opt_all = NULL;
		free(tmp);
		tmp = NULL;
		(*e)->opt_all = new;
		new = NULL;
	}
}

void		opt_exist_letter(char *str, t_opt **e, int i, int a)
{
	while (str[i] != '\0')
	{
		add_all_option(str, e, i);
		while ((*e)->opt != NULL && (*e)->opt[a] != '\0' &&
	str[i] != (*e)->opt[a])
			a++;
		if ((*e)->opt == NULL || (*e)->opt[a] == '\0')
			add_option(str[i], e, 0);
		a = 0;
		i++;
	}
}
