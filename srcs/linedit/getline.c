/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:17:26 by amoreilh          #+#    #+#             */
/*   Updated: 2017/04/13 19:58:28 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_endgetlineloop(t_shell *sh, t_input *input, t_autocomp *autoc)
{
	ft_printbuf(I, autoc);
	term_resetterm(sh);
	ft_strdel(&I->prompt2);
	ft_strdel(&I->line);
	ft_strdel(&I->clipboard);
	return (1);
}

char	*ft_getline(t_input *input, t_shell *sh)
{
	int			i;
	char		*ret;
	char		buf[READBUFSIZE];
	t_autocomp	autoc;

	if (ft_initreadline(I, sh, &autoc) == NULL)
		return (NULL);
	if ((i = getline_loop(sh, input, buf, &autoc)) != 0)
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

char	return_term_resetterm(t_shell *sh, int ret)
{
	term_resetterm(sh);
	return (ret);
}

char	is_ml_fct(t_shell *sh, t_input *input, char **ptr, char *new)
{
	if ((new = ft_getline(I, sh)) != NULL)
	{
		if (!(*ptr))
			(*ptr) = new;
		else
			(*ptr) = (STATE(sh->parser) == ST_HEREDOC && !sh->parser->eof)
				? ft_strjoinfree((*ptr), ft_strjoinfree(ft_strdup("\n"), new))
				: ft_strjoinfree((*ptr), new);
		if (!(*ptr))
			return (return_term_resetterm(sh, 1));
		return (return_term_resetterm(sh, 0));
	}
	return (return_term_resetterm(sh, 2));
}

char	event_loop(t_shell *sh, char **ptr)
{
	t_input		input;
	char		*new;
	t_redir		*red;

	red = NULL;
	new = NULL;
	if (!sh->parser && (I.prompt = 1))
		if (!(sh->parser = new_parser(sh->options)))
			return (1);
	red = get_current_redir(sh->parser);
	ptr = ((STATE(sh->parser) == ST_HEREDOC) && (red != NULL)) ? &(red->heredoc)
		: &(sh->parser->orig);
	if (IS_ML(sh->parser))
		return (is_ml_fct(sh, &input, ptr, new));
	else if ((*ptr))
	{
		free(*ptr);
		if (!((*ptr) = ft_getline(&I, sh)))
			return (return_term_resetterm(sh, 2));
	}
	else if (!((*ptr) = ft_getline(&I, sh)))
		return (return_term_resetterm(sh, 2));
	return (return_term_resetterm(sh, 0));
}
