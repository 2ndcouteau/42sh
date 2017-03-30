/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 15:24:17 by amoreilh          #+#    #+#             */
/*   Updated: 2017/03/23 17:57:35 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_initstruct(t_input *input, char mode)
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
	if (mode == 0)
	{
		ft_getcurscoords(I);
		I->savecursx = I->cursx;
		I->savecursy = I->cursy;
	}
}

/*
**	This function is never call...
*/

// char		*ft_ctrldc(char *buf, t_shell *sh, t_input *input
// 	, t_autocomp *autoc)
// {
// 	if (buf[0] == 4 && buf[1] == 0 // not used
// 		&& ((int)ft_strlen(I->line) <= I->prompt2len))
// 	{
// 		ft_endgetlineloop(sh, I, autoc);
// 		return (NULL);
// 	}
// 	else if (buf[0] == 3 && buf[1] == 0)
// 	{
// 		(void)buf;
// 		(void)sh;
// 		(void)autoc;
// 		free(input->prompt2);
// 		free(input->line);
// 		if (!input->prompt)
// 		{
// 			ft_getcurscoords(input);
// 			ft_cursgoto(0, input->cursy, 1);
// 		}
// 		return (ft_strnew(0));
// 	}
// 	else
// 		return (ft_strnew(0));
// }


// This function create and init the buffer of the ->line for receive all input of the user.
char		*ft_initreadline(t_input *input, t_shell *sh, t_autocomp *autoc)
{
	I->buffsize = BUFFSIZE;		// why init this variable here  ??
	I->ret = NO_ACTION;
	if (!(I->line = (char *)ft_memalloc(sizeof(char) * (I->buffsize * 10))))	// Why malloc 10 times the buffsize_len  why not just 2 ?
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
	ft_initstruct(I, 0);
	ft_displaypromptline(I);
	return (I->line);
}
