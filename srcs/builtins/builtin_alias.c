/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 20:03:19 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/20 11:26:34 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int			builtin_alias(t_shell *shell, char **argv)
{
	size_t	len;

	len = ft_stablen(argv);
	if (len == 1)
		print_str_dict(shell->options->aliases);
	else if (len == 2)
		dict_set(shell->options->aliases, new_cell(ft_strdup(argv[1]),
			ft_strnew(0), &free));
	else if (len >= 3)
	{
		if (!check_varname_format(argv[1]))
		{
			ft_fdprintf(2, "alias: bad varname format");
			return (1);
		}
		dict_set(shell->options->aliases, new_cell(ft_strdup(argv[1]),
			ft_stabjoin(" ", &argv[2]), &free));
	}
	return (0);
}

int			builtin_unalias(t_shell *shell, char **argv)
{
	size_t	len;

	len = ft_stablen(argv);
	if (len == 2)
		dict_del(shell->options->aliases, argv[1]);
	else
	{
		ft_fdprintf(2, "usage: unalias <key>\n");
		return (1);
	}
	return (0);
}
