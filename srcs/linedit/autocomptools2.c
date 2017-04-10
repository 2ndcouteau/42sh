/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomptools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:18:21 by amoreilh          #+#    #+#             */
/*   Updated: 2017/04/10 17:11:48 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		ft_folderorglob_isfolder(t_autocomp *autoc, t_input *input)
{
	char			*temp;

	temp = A->str;
	A->str = ft_strjoin(temp, "/");
	ft_strdel(&temp);
	ft_memmove(&I->line[I->bufpos + 1], &I->line[I->bufpos], 1);
	ft_strncpy(&I->line[I->bufpos], "/", 1);
	ft_cursgoto(I->savecursx, I->savecursy, 1);
	I->bufx++;
	ft_putstr(I->line);
	I->bufpos++;
}

static void		globbing_paste(t_input *input, char *clipboard)
{
	int pastelen;

	if (clipboard != NULL)
	{
		pastelen = ft_strlen(clipboard);
		while (I->bufposmax + pastelen >= I->buffsize)
			linedit_reallocbuff(I);
		ft_memmove(&I->line[I->bufpos + pastelen],
			&I->line[I->bufpos],
			(int)ft_strlen(&I->line[I->bufpos]));
		ft_strncpy(&I->line[I->bufpos],
			clipboard, (int)ft_strlen(clipboard));
	}
}

void			ft_folderorglob(t_autocomp *autoc, t_input *input)
{
	t_starmatch		*match;
	char			*endsave;

	match = NULL;
	endsave = NULL;
	ft_cursgoto(input->savecursx, input->savecursy - 1, 1);
	ft_putchar('\n');
	ft_cursgoto(input->savecursx, input->savecursy - 1, 1);
	if (A->str && (ft_strchr(A->str, '*')) && (I->line[I->bufpos - 1] == '/'))
		I->line[I->bufpos - 1] = ' ';
	else if (A->str && (I->line[I->bufpos - 1] != '/') &&
														ft_strchr(A->str, '*'))
		if ((match = ft_getword(I->bufpos - ft_strlen(A->str) + 1, I->line, I)))
		{
			endsave = ft_strdup(&input->line[input->bufpos]);
			ft_checkdir(match, input);
			globbing_paste(input, endsave);
			free(endsave);
		}
	if (A->str && !term_isfolder(A->str) && (I->line[I->bufpos - 1] != '/'))
		ft_folderorglob_isfolder(A, I);
}
