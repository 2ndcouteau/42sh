/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_comphist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:18:13 by amoreilh          #+#    #+#             */
/*   Updated: 2017/03/23 17:39:30 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


// This function will find a previous line use with the same previous cursor part.
char	hist_comphist(t_input *input, t_shell *sh, char upndown)
{
	char	*histline;
	int		lenhist;
	int		bufpos;

	if (STATE(sh->parser) != ST_NORM)			// If the line is not in the normal/basic mode
		return (NO_ACTION);
	// get the history line wich match with the current line $$ Here the arrow change the comportement
	histline = get_history(sh, &input->line[input->prompt2len]
	, input->bufpos - input->prompt2len, upndown);

	// if histline is NULL reassign the current line to the history line
	if (!histline)
		return (NO_ACTION);
//		histline = ft_strdup(&input->line[input->prompt2len]);	// dup the current line without the prompt
	if (histline && ft_strnequ(&input->line[input->prompt2len],					// If the current line is like the begin of the history line then
		histline, (input->bufpos - input->prompt2len)))							// copy the rest of the history line in the current line
	{
		bufpos = input->bufpos;						// position cursor
		// Clean the right part line of the cursor
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
