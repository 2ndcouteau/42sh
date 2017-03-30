/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_clean_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 05:38:29 by qrosa             #+#    #+#             */
/*   Updated: 2017/02/22 20:11:46 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	cd_check_double_dote(char **mytab, int cpt, int valid)
{
	mytab[cpt] = ft_free_line(&mytab[cpt]);
	mytab[cpt] = NULL;
	while (mytab[valid] == NULL && valid > 0)
		valid--;
	if (mytab[valid] != NULL)
		mytab[valid] = ft_free_line(&mytab[valid]);
	return (valid);
}

static char	**cd_epure_line(char **current_pwd, int *len_tab)
{
	int		valid;
	int		cpt;
	char	**mytab;

	valid = 0;
	cpt = 0;
	mytab = ft_strsplit(*current_pwd, '/');
	while (mytab[cpt] != NULL)
	{
		if (ft_strncmp(mytab[cpt], "..", 3) == 0)
			valid = cd_check_double_dote(mytab, cpt, valid);
		else if (ft_strncmp(mytab[cpt], ".", 2) == 0)
			mytab[cpt] = ft_free_line(&mytab[cpt]);
		else
			valid = cpt;
		cpt++;
	}
	*len_tab = cpt;
	return (mytab);
}

static void	cd_join_path(char **mytab, char **current_pwd, int len_tab)
{
	int		cpt;
	int		pos;
	int		line;

	pos = 0;
	line = 0;
	while (pos < len_tab)
	{
		cpt = 0;
		if (mytab[pos] != NULL)
		{
			(*current_pwd)[line++] = '/';
			while ((mytab[pos])[cpt] != '\0')
			{
				(*current_pwd)[line] = (mytab[pos])[cpt];
				line++;
				cpt++;
			}
			mytab[pos] = ft_free_line(&mytab[pos]);
		}
		pos++;
	}
	if (line == 0)
		(*current_pwd)[line++] = '/';
	(*current_pwd)[line] = '\0';
}

void		cd_clean_path(char **current_pwd)
{
	char	**mytab;
	int		len_tab;

	mytab = cd_epure_line(current_pwd, &len_tab);
	ft_bzero(*current_pwd, PATH_MAX);
	cd_join_path(mytab, current_pwd, len_tab);
	free(mytab);
	mytab = NULL;
}
