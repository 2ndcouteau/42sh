/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline_put_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoko <yoko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:36:59 by yoko              #+#    #+#             */
/*   Updated: 2017/03/27 21:28:48 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	getline_put_line(t_input *input, char *buf, t_shell *sh,
	t_autocomp *autoc)
{
	unsigned long	*buff_conv;

	buff_conv = (unsigned long *)buf;
	I->termw = tgetnum("co");
	I->termh = tgetnum("li");
	if (*buff_conv == CAPS_TAB && (I->comp = 1) && I->prompt)
		I->ret = comp_autocomp(I, autoc);							// Need to modifie return (status) sub-management
	else if (*buff_conv == CAPS_ARROW_UP || *buff_conv == CAPS_ARROW_DOWN || *buff_conv == CAPS_MAJ_DOWN)
		I->ret = hist_comphist(I, sh, buf[2] - 65);

// after this point the line is print again.
	if (I->ret > NO_ACTION)
	{
		if (!I->comp)	// bool autocompletion. it is useful because autocomp write too
			ft_printbuf(I, autoc);
		I->comp = 0;
		if (!ft_strchr(I->line, '\n') && !I->comp)						// Block the cursor when multi_line history
			ft_cursgoto(I->bufx + 1, (I->savecursy + I->bufy), 1);
		else if ((I->multi = 1) && !I->comp)
			ft_cursgoto(I->prompt2len + 1, (I->savecursy), 1);
		if ((I->bufposmax + 1) >= I->buffsize)
			linedit_reallocbuff(I);
	}
}
