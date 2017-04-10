/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_stdout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoko <yoko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 13:00:03 by yoko              #+#    #+#             */
/*   Updated: 2017/04/09 18:29:11 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	my_outc(int c)
{
	return ((int)write(STDOUT_FILENO, &c, 1));
}

int			put_stdout(char *opt)
{
	char	*res;

	if ((res = tgetstr(opt, NULL)) == NULL)
		return (1);
	tputs(res, 0, my_outc);
	return (0);
}

int			ft_putc(int c)
{
	write(1, &c, 1);
	return (1);
}
