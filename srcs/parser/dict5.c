/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 16:27:15 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/06 21:09:39 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**dict2env(t_dict *dict)
{
	t_cell	*iterator;
	char	**env;
	size_t	cpt;

	if (!dict)
		return (NULL);
	if (!(env = ft_stabnew(dict_len(&dict) + 1)))
		return (NULL);
	iterator = NULL;
	cpt = 0;
	while ((iterator = dict_next(dict, iterator)) != NULL)
		env[cpt++] = ft_strjoin3(iterator->key, "=", iterator->value);
	env[cpt] = 0;
	return (env);
}

t_dict		*cpy_dict_env(t_dict *dict)
{
	t_dict	*new;
	char	**tab_tmp;

	tab_tmp = dict2env(dict);
	new = env2dict(tab_tmp);
	ft_stabdel(&tab_tmp);
	return (new);
}

static void	set_hashtab(t_dict *dct, char *name, int i, char **binpaths)
{
	t_cell	*cell;

	if ((cell = new_cell(ft_strdup(name),\
		ft_strdup(binpaths[i]), &del_str_value)) == NULL ||
		cell->key == NULL)
		del_cell(&cell);
	else
		dict_set_doublon(dct, cell);
}

void		parse_binpaths(t_dict *binhashtab, char **binpaths)
{
	DIR				*directory;
	struct dirent	*folder;
	int				i;

	i = -1;
	while (binpaths[++i])
		if (binpaths[i] && (ft_strlen(binpaths[i]) > 0) &&
			!ft_strequ(".", binpaths[i]) && !ft_strequ("..", binpaths[i]) &&
			(directory = opendir(binpaths[i])))
		{
			while ((folder = readdir(directory)))
				if (ft_strlen(folder->d_name) > 0)
					if ((ft_strlen(folder->d_name) > 0) && binpaths[i] &&
						!ft_strequ(".", folder->d_name) &&
						!ft_strequ("..", folder->d_name))
						set_hashtab(binhashtab, folder->d_name, i, binpaths);
			closedir(directory);
		}
}

t_dict		*createbin_hashtab(char *path)
{
	char			**binpaths;
	t_dict			*binhashtab;

	if (!path)
	{
		binhashtab = new_dict(128);
		return (binhashtab);
	}
	else if (!(binpaths = ft_strsplit(path, ':'))
	|| !(binhashtab = new_dict(128)))
		return (NULL);
	parse_binpaths(binhashtab, binpaths);
	ft_freetab(&binpaths);
	return (binhashtab);
}
