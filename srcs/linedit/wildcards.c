/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:18:21 by amoreilh          #+#    #+#             */
/*   Updated: 2017/01/19 15:18:23 by amoreilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_star(char *word, char *wild)
{
	if (*word != '\0' && *wild == '*')
		return (ft_star(word + 1, wild) || ft_star(word, wild + 1));
	if (*word == '\0' && *wild == '*')
		return (ft_star(word, wild + 1));
	if (*word == *wild && *word != '\0' && *wild != '\0')
		return (ft_star(word + 1, wild + 1));
	if (*word == *wild && *word == '\0')
		return (1);
	return (0);
}

void		ft_checkdirloop(struct dirent *f, t_input *input,
	t_starmatch *match, int *pos)
{
	int		len;
	char	*dname;

	dname = ft_strdup(f->d_name);
	if (*pos + ((int)ft_strlen(dname) + match->pathlen + 1)
	>= (input->buffsize - 2))
		linedit_reallocbuff(input);
	if ((dname[0] != '.' && ft_star(dname, match->word))
	|| (match->word[0] == '.' && ft_star(dname, match->word)))
	{
		if (*pos == match->wordpos)
			while (input->line[*pos] && !ft_isspace(input->line[*pos])
			&& (*pos + 1 < input->buffsize))
				ft_memmove(&input->line[*pos], &input->line[*pos + 1],
					ft_strlen(&input->line[*pos]));
		ft_insertmatch(dname, match, *pos, input);
		len = (ft_strlen(dname) + match->pathlen + 1);
		input->bufpos += len;
		*pos += len;
	}
	free(dname);
}

void		ft_checkdir(t_starmatch *match, t_input *input)
{
	DIR						*folder;
	struct dirent			*f;
	int						pos;

	if (match)
	{
		pos = match->wordpos;
		ft_getmatchforlder(match);
	}
	if (!(folder = opendir(match->path)))
	{
		if (match)
			ft_freematch(match);
		return ;
	}
	while ((f = readdir(folder)) && match)
		ft_checkdirloop(f, input, match, &pos);
	input->bufpos = pos;
	ft_freematch(match);
	closedir(folder);
}

void		ft_getmatchingfiles(t_input *input)
{
	int			i;
	t_starmatch *match;

	i = 0;
	while (input->line[i])
	{
		if (input->line[i] == '*')
		{
			match = ft_getword(i, input->line, input);
			if (match)
				ft_checkdir(match, input);
		}
		i++;
	}
}
