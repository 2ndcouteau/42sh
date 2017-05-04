/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 16:38:30 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/22 16:23:31 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_left_redir(t_parser *p, int *idx)
{
	int		i;
	char	*red;

	i = *idx;
	while (ft_isdigit(p->orig[i]))
		i++;
	if (p->orig[i] != '<' && p->orig[i] != '>')
		return (NULL);
	if (i == *idx)
		return (NULL);
	red = ft_strsub(p->orig, (*idx), i - (*idx));
	(*idx) = i;
	return (red);
}

int		get_rtype(t_parser *p, int *idx)
{
	char	t;

	t = p->orig[*idx];
	if (t != '>' && t != '<')
		return (-1);
	(*idx)++;
	if (p->orig[*idx] == t)
	{
		(*idx)++;
		return (t == '<' ? HEREDOC : REDAPPEND);
	}
	return (t == '<' ? REDIN : REDOUT);
}

char	*get_red_fdout(t_parser *p, int *idx)
{
	int		i;
	char	*red;

	i = *idx;
	if (p->orig[*idx] != '&')
		return (NULL);
	(*idx)++;
	if (p->orig[*idx] == '-')
		(*idx)++;
	else
		while (ft_isdigit(p->orig[(*idx)]))
			(*idx)++;
	red = ft_strsub(p->orig, i, (*idx) - i);
	p->idx = *idx;
	return (red);
}

void	destroy_redir(t_redir **red)
{
	if ((*red)->fdin != NULL)
		ft_strdel(&((*red)->fdin));
	if ((*red)->arg != NULL)
		ft_strdel(&((*red)->arg));
	if ((*red)->arg != NULL)
		ft_strdel(&((*red)->arg));
	if ((*red)->heredoc != NULL)
		ft_strdel(&((*red)->heredoc));
	ft_memdel((void **)&*red);
	(*red) = NULL;
}

char	*human_redtype(int redtype)
{
	if (redtype == REDIN)
		return ("<");
	else if (redtype == REDOUT)
		return (">");
	else if (redtype == REDAPPEND)
		return (">>");
	else if (redtype == HEREDOC)
		return ("<<");
	return ("Unreconized");
}
