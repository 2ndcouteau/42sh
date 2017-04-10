/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:16:48 by amoreilh          #+#    #+#             */
/*   Updated: 2017/04/10 17:09:19 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#define A autoc
#define I input

void			ft_insertchoice(t_input *input, char *choice, t_autocomp *autoc)
{
	int wlen;

	wlen = ft_strlen(choice);
	if (!choice)
		return ;
	while (I->bufpos + wlen > I->buffsize - 1)
		linedit_reallocbuff(input);
	if (I->bufpos + wlen < I->buffsize)
	{
		ft_memmove(&I->line[I->bufpos + (wlen - A->len)],
			&I->line[I->bufpos], ft_strlen(&I->line[I->bufpos]) + 1);
		ft_strncpy(&I->line[I->bufpos - A->len], choice, wlen);
		I->bufposmax = ft_strlen(I->line);
		I->bufpos = I->bufpos + wlen - A->len;
	}
	if (!I->multi)
		I->bufx = (I->bufpos - (I->termw * I->bufy));
}

t_compnode		*ft_compkeyhook(t_input *input, t_autocomp *autoc, char *buf,
	t_compnode *cur)
{
	(void)input;
	(void)autoc;
	if (cur && buf[0] == 27 && buf[1] == 91 && buf[2] == 68 && cur->index != 0)
	{
		cur->isover = 0;
		cur = (cur->head.prev) ? GET_NODE(cur->head.prev, t_compnode, head)
		: NULL;
		cur->isover = 1;
	}
	if (cur && buf[0] == 27 && buf[1] == 91 && buf[2] == 67 && cur->head.next)
	{
		cur->isover = 0;
		cur = (cur->head.next) ? GET_NODE(cur->head.next, t_compnode, head)
		: NULL;
		cur->isover = 1;
	}
	else
		cur->isover = 1;
	ft_bzero(buf, READBUFSIZE);
	ft_displaycomplist(autoc, input);
	ft_cursgoto(I->bufx + 1, (I->savecursy + I->bufy), 1);
	if (cur->index != 0)
		cur->isover = 0;
	return (cur);
}

char			*ft_compreadloop(t_input *input, t_autocomp *autoc)
{
	char		buf[READBUFSIZE];
	t_compnode	*cur;

	cur = (A->first->head.next) ?
	GET_NODE(A->first->head.next, t_compnode, head) : NULL;
	cur->isover = 1;
	ft_getlistsize(autoc, input);
	ft_displaycomplist(autoc, input);
	ft_cursgoto(I->bufx + 1, (I->savecursy + I->bufy), 1);
	ft_bzero(buf, READBUFSIZE);
	while (read(0, buf, READBUFSIZE) > 0)
	{
		ft_getlistsize(autoc, input);
		if (buf[0] == 10 && buf[1] == 0)
			break ;
		if (buf[0] == 27 && buf[1] == 0 && buf[2] == 0)
		{
			I->comp = 0;
			return (NULL);
		}
		cur = ft_compkeyhook(input, autoc, buf, cur);
	}
	return (cur->word);
}

void			ft_dispcomp(t_autocomp *autoc, t_input *input)
{
	t_compnode *cur;

	cur = (A->first->head.next) ?
	GET_NODE(A->first->head.next, t_compnode, head) : NULL;
	ft_getlistsize(autoc, input);
	if (A->i == 0)
	{
		I->comp = 0;
		return ;
	}
	if (A->nbwords >= 2)
		A->choice = ft_compreadloop(input, autoc);
	else
		(A->choice = cur->word);
	if ((ft_strlen(A->str) > 0) && ft_strrchr(A->str, '/') && A->choice)
	{
		A->choice = ft_strjoin(A->str, A->choice);
		ft_insertchoice(input, A->choice, autoc);
		free(A->choice);
	}
	else if (A->choice)
		ft_insertchoice(input, A->choice, autoc);
	A->nbwords = 0;
}

int				comp_autocomp(t_input *input, t_autocomp *autoc)
{
	A->i = 0;
	A->dir = NULL;
	A->pathlen = 0;
	A->path = NULL;
	A->str = comp_firstletters(input);
	ft_folderorglob(autoc, input);
	if ((A->str) && ft_strlen(A->str) > 0)
	{
		ft_getfolder(autoc, input);
		ft_getlist(autoc);
		if (!ft_strchr(A->str, '*'))
			ft_getlistsize(autoc, input);
		if (I->nblines + A->nblines + 1 >= I->termh)
		{
			ft_putstr("\nWindow size too small");
			ft_freecomplist(autoc);
			free(A->str);
			return (NO_ACTION);
		}
		(!ft_strchr(A->str, '*')) ? ft_dispcomp(autoc, input) : 1;
		ft_freecomplist(autoc);
	}
	ft_strdel(&A->str);
	I->comp = 0;
	return (PRINT_AND_CURSOR);
}
