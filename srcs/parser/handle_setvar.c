/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_setvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 21:10:08 by ljohan            #+#    #+#             */
/*   Updated: 2017/03/01 00:03:50 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	handle_setvar_suite(t_parser *p)
{
	if (!p->part)
		p->part = ft_strdup("=");
	else
		p->part = ft_strjoinfree(p->part, ft_strdup("="));
	pop_state(&(p->states));
}

void		handle_setvar(t_shell *shell, t_parser *p)
{
	char	*var;
	char	*val;
	t_cell	*cell;

	p->idx++;
	if (p->part != NULL && ft_strcmp(p->part, "") != 0)
	{
		var = ft_strdup(p->part);
		ft_strdel(&(p->part));
		val = implicit_parse_one(shell, p);
		if (ft_strcmp(val, "") == 0)
		{
			dict_del(p->opts->vars, var);
			ft_strdel(&val);
			pop_state(&(p->states));
			return ;
		}
		else if ((cell = new_cell(var, val, &del_str_value)) != NULL)
		{
			dict_set(p->opts->vars, cell);
			pop_state(&(p->states));
			return ;
		}
	}
	handle_setvar_suite(p);
}
