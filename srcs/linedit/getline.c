/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:17:26 by amoreilh          #+#    #+#             */
/*   Updated: 2017/03/27 20:44:55 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_endgetlineloop(t_shell *sh, t_input *input, t_autocomp *autoc)
{
	ft_printbuf(I, autoc);
	term_resetterm(sh);
	ft_strdel(&I->prompt2);
	ft_strdel(&I->line);
	return (1);
}

// get the new inputs
char	*ft_getline(t_input *input, t_shell *sh)
{
	int			i;
	char		*ret;
	char		buf[READBUFSIZE];
	t_autocomp	autoc;

	if (ft_initreadline(I, sh, &autoc) ==  NULL)		// init the buffer a the new char
		return (NULL);
	if ((i = getline_loop(sh, input, buf, &autoc)) != 0)	// get new inputs
	{
		if (i == 1)
			return (ft_strdup("exit"));
		else
			return (NULL);
	}
	ret = ((int)ft_strlen(I->line) > I->prompt2len)
		? ft_strdup(&I->line[I->prompt2len]) : ft_strnew(0);
	ft_endgetlineloop(sh, I, &autoc);
	return (ret);
}

char	event_loop(t_shell *sh, char **ptr)
{
	t_input input;
	char	*new;
	t_redir *red;

	red = NULL;
	new = NULL;
	if (!sh->parser && (I.prompt = 1))
		if (!(sh->parser = new_parser(sh->options)))
			return (1);
	red = get_current_redir(sh->parser);
	ptr = ((STATE(sh->parser) == ST_HEREDOC) && (red != NULL)) ? &(red->heredoc)
		: &(sh->parser->orig);
	if (IS_ML(sh->parser))
	{
		if ((new = ft_getline(&I, sh)) != NULL) // get the news inputs
		{
			if (!(*ptr))
				(*ptr) = new;
			else
				(*ptr) = (STATE(sh->parser) == ST_HEREDOC && !sh->parser->eof)				// HEREDOC Management
					? ft_strjoinfree((*ptr), ft_strjoinfree(ft_strdup("\n"), new))
					: ft_strjoinfree((*ptr), new);
			if (!(*ptr))
			{
				term_resetterm(sh);
				return (1);
			}
		}
		else
		{
			term_resetterm(sh);
			return (2);
		}
	}
	else if ((*ptr))
	{
		free(*ptr);
		if (!((*ptr) = ft_getline(&I, sh)))
		{
			term_resetterm(sh);
			return (2);
		}
	}
	else if (!((*ptr) = ft_getline(&I, sh)))
	{
		term_resetterm(sh);
		return (2);
	}
	term_resetterm(sh);
	return (0);
}
