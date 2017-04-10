/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_comphist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:18:13 by amoreilh          #+#    #+#             */
/*   Updated: 2017/04/10 16:47:45 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	hist_comphist(t_input *input, t_shell *sh, char upndown)
{
	char	*histline;
	int		lenhist;
	int		bufpos;

	if (STATE(sh->parser) != ST_NORM)
		return (NO_ACTION);
	histline = get_history(sh, &input->line[input->prompt2len]
	, input->bufpos - input->prompt2len, upndown);
	if (!histline)
		return (NO_ACTION);
	if (histline && ft_strnequ(&input->line[input->prompt2len],
		histline, (input->bufpos - input->prompt2len)))
	{
		bufpos = input->bufpos;
		ft_bzero(&input->line[input->bufpos], input->buffsize - input->bufpos);
		lenhist = ft_strlen(histline);
		while (((input->buffsize - input->prompt2len) < lenhist))
			linedit_reallocbuff(input);
		ft_strncpy(&input->line[input->bufpos],
			&histline[input->bufpos - input->prompt2len],
			(lenhist - (input->bufpos - input->prompt2len)));
		input->bufpos = bufpos;
		return (PRINT_AND_CURSOR);
	}
	return (NO_ACTION);
}
