/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 17:08:39 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/06 21:08:37 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_str_dict(t_dict *dct)
{
	t_cell	*iterator;

	iterator = NULL;
	while ((iterator = dict_next(dct, iterator)) != NULL)
	{
		ft_printf("%s=\"%s\"\n", iterator->key, iterator->value);
	}
}

void	push_cell(t_cell **cells, t_cell *cell)
{
	if ((*cells) == NULL)
		(*cells) = cell;
	else
		list_append(&((*cells)->head), &(cell->head));
}

void	test_dict(t_shell *shell, int ac, char **av, char **env)
{
	t_dict	*denv;

	(void)ac;
	(void)av;
	(void)env;
	(void)shell;
	denv = env2dict(env);
	dict_set(denv, new_cell(ft_strdup("_oko"), ft_strdup("tkt"), &free));
	debug_dict(denv);
	dict_set(denv, new_cell(ft_strdup("_oko"), ft_strdup("oups"), &free));
	debug_dict(denv);
	dict_set(denv, new_cell(ft_strdup("_koo"), ft_strdup("re"), &free));
	dict_del(denv, "ok");
	debug_dict(denv);
	dict_set(denv, new_cell(ft_strdup("_oko"), ft_strdup("oups"), &free));
	debug_dict(denv);
	dict_set(denv, new_cell(ft_strdup("_koo"), ft_strdup("aie"), &free));
	debug_dict(denv);
}

t_cell	*dict_pop(t_dict *dict, char *key)
{
	t_cell *c;
	t_head *hc;

	c = dict_get(dict, key);
	if (c)
	{
		if (c->head.prev == NULL)
		{
			hc = &(c->head);
			list_pop_first(&hc);
			if (hc == NULL)
				dict->cells[(key_hash(c->key) % dict->size)] = NULL;
			else
				dict->cells[(key_hash(c->key) % dict->size)] = \
					GET_NODE(hc, t_cell, head);
		}
		else
			list_pop_one(&(c->head));
	}
	return (c);
}
