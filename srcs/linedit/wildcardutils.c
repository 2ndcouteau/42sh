/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcardutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 17:18:15 by amoreilh          #+#    #+#             */
/*   Updated: 2017/04/27 18:49:34 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_getmatchforlder(t_starmatch *match)
{
	char *temp;
	char *slash;

	if (match->word)
	{
		if ((slash = (ft_strrchr(match->word, '/'))))
		{
			match->pathlen = (ft_strlen(match->word) - (ft_strlen(slash))) + 1;
			match->path = ft_strsub(match->word, 0, match->pathlen);
			temp = match->word;
			match->word = ft_strdup(slash + 1);
			match->wordlen = ft_strlen(match->word);
			free(temp);
		}
		else
		{
			match->path = ft_strdup("./");
			match->wordlen = ft_strlen(match->word);
			match->pathlen = 2;
		}
	}
}

t_starmatch	*getword_suite(t_starmatch *match, char *line, int wstart,
	int wend)
{
	match->word = ft_strsub(line, wstart, (wend - wstart));
	if (g_debug[0])
		ft_fdprintf(g_debug[1], "\nmatch->word={%s}\n", match->word);
	match->wordlen = (wend - wstart);
	match->wordpos = wstart;
	return (match);
}

t_starmatch	*ft_getword(int pos, char *line, t_input *input)
{
	int			wstart;
	int			wend;
	t_starmatch *match;

	wstart = pos - 1;
	wend = pos;
	if (!(match = (t_starmatch *)ft_memalloc(sizeof(t_starmatch))))
		exit(0);
	while (wstart >= input->prompt2len && !(ft_isspace(line[wstart])))
		wstart--;
	while (wend <= input->bufposmax && !(ft_isspace(line[wend])))
		wend++;
	if (g_debug[0])
		ft_fdprintf(g_debug[1],
			"\ninput->prompt2len = %d wend = %d, wstart= %d\n"
			, input->prompt2len, wend, wstart);
	if (wend - (++wstart) > 0)
		return (getword_suite(match, line, wstart, wend));
	free(match);
	return (NULL);
}

void		ft_freematch(t_starmatch *match)
{
	if (match->word)
		free(match->word);
	if (match->path)
		free(match->path);
	if (match)
		free(match);
	match->word = NULL;
	match->path = NULL;
	match = NULL;
}

int			ft_insertmatch(char *word, t_starmatch *match,
	int pos, t_input *input)
{
	int len;
	int wlen;

	wlen = ft_strlen(word);
	len = wlen + match->pathlen;
	if (ft_strequ(match->path, "./"))
		match->pathlen = 0;
	if (((int)ft_strlen(input->line) + len + 1) > input->buffsize)
		linedit_reallocbuff(input);
	ft_strncpy(&input->line[pos], match->path, match->pathlen);
	ft_strncpy(&input->line[pos + match->pathlen], word, wlen);
	ft_strncpy(&input->line[pos + match->pathlen + wlen], " ", 1);
	ft_nblines(input);
	return (0);
}
