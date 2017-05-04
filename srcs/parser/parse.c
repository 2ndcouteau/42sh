/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 18:36:38 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/18 14:55:55 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*parse_quote(t_parser *p)
{
	char	*part;
	char	*tmp;

	tmp = forward_escape(CURRENT(p), "'");
	part = ft_strsub(p->orig, p->idx, tmp - CURRENT(p));
	p->idx += tmp - CURRENT(p);
	return (part);
}

char	*parse_string(t_parser *p)
{
	char	*part;
	char	*tmp;

	tmp = FWD_STR(CURRENT(p));
	part = ft_strsub(p->orig, p->idx, tmp - CURRENT(p));
	p->idx += tmp - CURRENT(p);
	return (part);
}

char	*parse_var(t_parser *p)
{
	char	*var;
	char	*val;

	val = FWD_VAR(CURRENT(p));
	if ((var = ft_strsub(p->orig, p->idx, val - CURRENT(p))) == NULL)
		return (NULL);
	p->idx += ft_strlen(var);
	if ((val = ft_getenv(p->opts->env, var)) != NULL)
	{
		ft_strdel(&var);
		return (ft_strdup(val));
	}
	else if ((val = ft_getenv(p->opts->vars, var)) != NULL)
	{
		ft_strdel(&var);
		return (ft_strdup(val));
	}
	return (ft_strjoinfree(ft_strdup("$"), var));
}
