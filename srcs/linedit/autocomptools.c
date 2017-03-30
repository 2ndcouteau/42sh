/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomptools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:18:21 by amoreilh          #+#    #+#             */
/*   Updated: 2017/03/21 13:46:01 by yoko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#define A autoc
#define I input

t_compnode		*ft_makecompnode(char *name)
{
	t_compnode *node;

	if (!(node = (t_compnode *)ft_memalloc(sizeof(t_compnode))))
		exit(1);
	node->padding = 0;
	node->wordlen = 0;
	node->isover = 0;
	node->head.next = NULL;
	node->index = 0;
	if (!(node->word = ft_strdup(name)))
		exit(1);
	node->head.prev = NULL;
	return (node);
}

void			ft_getfolder(t_autocomp *autoc, t_input *input)
{
	char *temp;
	char *slash;

	if (!A->str)
		return ;
	if ((slash = (ft_strrchr(A->str, '/'))))
	{
		A->pathlen = (ft_strlen(A->str) - (ft_strlen(slash))) + 1;
		A->path = ft_strsub(A->str, 0, A->pathlen);
		temp = A->str;
		A->str = ft_strdup(slash + 1);
		free(temp);
	}
	else
	{
		if (ft_isfirstword(input, I->line))
			A->path = ft_strdup("/bin");
		else
			A->path = ft_strdup("./");
	}
	A->len = ft_strlen(A->str);
	A->dir = opendir(A->path);
	free(A->path);
}

void			ft_getlistsize(t_autocomp *autoc, t_input *input)
{
	t_compnode *cur;

	A->nbwords = 0;
	A->nbwperline = 0;
	A->maxwlen = 0;
	cur = (A->first->head.next) ?
	GET_NODE(A->first->head.next, t_compnode, head) : NULL;
	while (cur)
	{
		cur->wordlen = (int)ft_strlen(cur->word);
		A->maxwlen = (A->maxwlen > cur->wordlen) ? A->maxwlen : cur->wordlen;
		A->nbwords++;
		cur = (cur->head.next) ? GET_NODE(cur->head.next, t_compnode, head)
		: NULL;
	}
	A->maxwlen++;
	A->nbwperline = (I->termw) / A->maxwlen;
	A->nblines = ft_complines(autoc, input) + 1;
}
