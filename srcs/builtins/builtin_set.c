/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 17:42:29 by ljohan            #+#    #+#             */
/*   Updated: 2017/04/27 21:44:41 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		builtin_set(t_shell *shell, char **argv)
{
	size_t	len;

	len = ft_stablen(argv);
	if (len == 1)
		print_str_dict(shell->options->vars);
	else if (len == 2)
		dict_set(shell->options->vars, new_cell(ft_strdup(argv[1]),
			ft_strnew(0), &free));
	else if (len == 3)
	{
		if (!check_varname_format(argv[1]))
		{
			ft_fdprintf(2, "set: bad varname format");
			return (1);
		}
		dict_set(shell->options->vars, new_cell(ft_strdup(argv[1]),
			ft_strdup(argv[2]), &free));
	}
	else
	{
		ft_fdprintf(2, "usage: set <key> [<value>]\n");
		return (1);
	}
	return (0);
}

int		builtin_unset(t_shell *shell, char **argv)
{
	size_t	len;

	len = ft_stablen(argv);
	if (len == 2)
		dict_del(shell->options->vars, argv[1]);
	else
	{
		ft_fdprintf(2, "usage: unset <key>\n");
		return (1);
	}
	return (0);
}
