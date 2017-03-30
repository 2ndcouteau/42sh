/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:16:56 by amoreilh          #+#    #+#             */
/*   Updated: 2017/01/19 15:41:02 by amoreilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_complines(t_autocomp *autoc, t_input *input)
{
	int			nbwords;
	int			nblines;
	int			nbonuslines;
	int			maxwordlen;
	t_compnode	*cur;

	nbwords = 0;
	nblines = 0;
	nbonuslines = 1;
	cur = (autoc->first->head.next)
	? GET_NODE(autoc->first->head.next, t_compnode, head) : NULL;
	while (cur && (maxwordlen = autoc->maxwlen))
	{
		nbwords++;
		if (nbwords >= autoc->nbwperline)
		{
			nblines++;
			nbwords = 0;
		}
		cur = (cur->head.next)
			? GET_NODE(cur->head.next, t_compnode, head) : NULL;
	}
	while (maxwordlen + 1 > input->termw && nbonuslines++)
		maxwordlen -= input->termw;
	return (nblines * (nbonuslines));
}

void	ft_printcompword(char *word, int padding, char select)
{
	if (select)
	{
		ft_putstr("\033[48;5;208m\033[38;5;240m");
		ft_putstr(word);
		while (padding-- > 1)
			ft_putchar(' ');
		ft_putstr("\033[0m");
		ft_putchar(' ');
	}
	else
		ft_putstr(word);
	while (padding--)
		ft_putchar(' ');
}

void	ft_displayloop(t_autocomp *autoc, t_input *input)
{
	int			padding;
	int			nbwords;
	t_compnode	*cur;

	nbwords = 0;
	(void)input;
	cur = (autoc->first->head.next) ?
	GET_NODE(autoc->first->head.next, t_compnode, head) : NULL;
	ft_cursgoto(input->savecursx, (input->savecursy + input->nblines + 1), 1);
	while (cur)
	{
		padding = autoc->maxwlen - cur->wordlen;
		if (cur->isover)
			ft_printcompword(cur->word, padding, 1);
		else
			ft_printcompword(cur->word, padding, 0);
		nbwords++;
		if (nbwords >= autoc->nbwperline)
		{
			ft_putchar('\n');
			nbwords = 0;
		}
		cur = (cur->head.next) ?
		GET_NODE(cur->head.next, t_compnode, head) : NULL;
	}
}

void	ft_displaycomplist(t_autocomp *autoc, t_input *input)
{
	int nblinestemp;

	nblinestemp = autoc->nblines;
	ft_cursgoto(input->savecursx, (input->savecursy + input->nblines + 1), 1);
	if (input->savecursy + input->nblines + autoc->nblines > input->termh)
	{
		while (nblinestemp--)
		{
			ft_putchar('\n');
			if (input->savecursy + input->nblines + autoc->nblines + 1
				> input->termh)
				input->savecursy--;
		}
	}
	ft_cursgoto(input->savecursx, (input->savecursy + input->nblines + 1), 1);
	ft_displayloop(autoc, input);
}

void	ft_getlist(t_autocomp *autoc)
{
	t_compnode		*next;
	struct dirent	*f;
	char			*word;

	autoc->first = ft_makecompnode("FIRST");
	autoc->i = 0;
	while (autoc->dir && (f = readdir(autoc->dir)))
	{
		word = ft_strdup(f->d_name);
		if ((autoc->len > 0 && ft_strnstr(word, autoc->str, autoc->len))
			|| (autoc->len <= 0))
		{
			next = ft_makecompnode(word);
			next->index = autoc->i;
			list_append(&(autoc->first->head), &(next->head));
			autoc->i++;
		}
		free(word);
	}
	if (autoc->dir)
	{
		closedir(autoc->dir);
		autoc->dir = NULL;
	}
}
