/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline_put_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoko <yoko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:36:59 by yoko              #+#    #+#             */
/*   Updated: 2017/04/10 16:45:15 by qrosa            ###   ########.fr       */
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
		I->ret = comp_autocomp(I, autoc);
	else if (*buff_conv == CAPS_ARROW_UP || *buff_conv == CAPS_ARROW_DOWN)
		I->ret = hist_comphist(I, sh, buf[2] - 65);
	if (I->ret > NO_ACTION)
	{
		if (!I->comp)
			ft_printbuf(I, autoc);
		I->comp = 0;
		ft_cursgoto(I->bufx + 1, (I->savecursy + I->bufy), 1);
		if ((I->bufposmax + 1) >= I->buffsize)
			linedit_reallocbuff(I);
	}
}
