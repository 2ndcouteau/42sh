/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 15:24:17 by amoreilh          #+#    #+#             */
/*   Updated: 2017/04/10 17:22:56 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_initstruct(t_input *input, t_shell *sh)
{
	I->termw = tgetnum("co");
	I->termh = tgetnum("li");
	I->comp = 0;
	I->end = 0;
	input->multi = 0;
	input->bufpos = I->prompt2len;
	I->bufx = I->prompt2len;
	I->bufy = 0;
	I->bufposmax = 0;
	I->clipboard = NULL;
	ft_getcurscoords(I, sh);
	I->savecursx = I->cursx;
	I->savecursy = I->cursy;
}

char		*ft_initreadline(t_input *input, t_shell *sh, t_autocomp *autoc)
{
	I->buffsize = BUFFSIZE;
	I->ret = NO_ACTION;
	if (!(I->line = (char *)ft_memalloc(sizeof(char) * I->buffsize)))
		return (NULL);
	autoc->nblines = 0;
	ft_bzero(I->line, I->buffsize);
	ft_prompt(I, sh);
	while ((I->prompt2len >= (I->buffsize - 1)))
	{
		if (linedit_reallocbuff(I) == NULL)
			return (NULL);
	}
	if (I->prompt2len < (I->buffsize - 1))
		ft_strncpy(I->line, I->prompt2, I->prompt2len);
	term_setterm(sh);
	ft_initstruct(I, sh);
	ft_displaypromptline(I);
	return (I->line);
}
