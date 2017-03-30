/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 13:10:53 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/24 17:02:56 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "dict.h"

t_help		*new_help(char *name, char *help, char *doc)
{
	t_help *h;

	if ((h = (t_help*)ft_memalloc(sizeof(t_help))) == NULL)
		return (NULL);
	h->name = name;
	h->help = help;
	h->doc = doc;
	return (h);
}

t_dict		*build_help(void)
{
	t_dict *help;

	if ((help = new_dict(14)) == NULL)
		return (NULL);
	help_set_help(help);
	help_set_env(help);
	help_set_setenv(help);
	help_set_unsetenv(help);
	help_set_jobs(help);
	help_set_fg(help);
	help_set_bg(help);
	help_set_alias(help);
	help_set_unalias(help);
	help_set_set(help);
	help_set_unset(help);
	help_set_history(help);
	help_set_echo(help);
	help_set_cd(help);
	return (help);
}

static void	print_help_cell(t_head *head)
{
	t_cell *cell;

	cell = GET_NODE(head, t_cell, head);
	ft_fdprintf(1, "%s: %s\n", cell->key,
		((char*)((t_help*)cell->value)->help));
}

int			ft_help(char **args)
{
	t_dict	*dhelp;
	t_cell	*cell;
	int		i;

	dhelp = build_help();
	if ((*args) == NULL)
		dict_iter(dhelp, &print_help_cell);
	else
	{
		i = -1;
		while (args[++i])
		{
			if ((cell = dict_get(dhelp, args[i])) == NULL)
				ft_fdprintf(1, "No help on %s.\n", args[i]);
			else
				ft_fdprintf(1, "%s: %s\n\t%s\n", cell->key
					, ((t_help*)cell->value)->help
					, ((t_help*)cell->value)->doc);
		}
	}
	destroy_dict(&dhelp);
	return (0);
}
