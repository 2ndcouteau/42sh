/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 15:42:42 by amoreilh          #+#    #+#             */
/*   Updated: 2017/04/10 16:45:46 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#define I input

int		ft_nblines(t_input *input)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	while (I->line[i++])
	{
		if (I->line[i] == '\n')
		{
			count++;
			j = 0;
		}
		j++;
		if (j / I->termw > 0)
		{
			j = 0;
			count++;
		}
	}
	return (count);
}

void	ft_displaypromptline(t_input *input)
{
	int arrowindex;
	int i;

	i = 0;
	arrowindex = ft_strlen(I->prompt2)
		- (ft_strlen((ft_strrchr(I->prompt2, '>'))));
	if (!I->prompt)
		while (i++ < arrowindex)
			write(2, " ", 1);
	else
		ft_putnstr_fd(I->line, arrowindex, 2);
	ft_putstr_fd("\033[38;5;208m", 2);
	ft_putnstr_fd(&I->line[arrowindex], 1, 2);
	if (ft_strchr(I->line, '\n'))
	{
		ft_putstr_fd("\033[38;5;240m", 2);
		print_special_putstr_fd(&I->line[arrowindex + 1], 2);
		ft_putstr_fd("\033[0m", 2);
	}
	else if (!ft_strchr(I->line, '\n'))
	{
		ft_putstr_fd("\033[0m", 2);
		ft_putstr_fd(&I->line[arrowindex + 1], 2);
	}
	(I->end || I->comp) ? ft_putchar('\n') : 1;
}

void	ft_printbuf(t_input *input, t_autocomp *autoc)
{
	int nlines;

	I->bufposmax = ft_strlen(I->line);
	I->nblines = ft_nblines(I);
	I->bufy = (I->bufpos / I->termw);
	I->bufx = (I->bufpos - (I->termw * I->bufy));
	I->bufxmax = (I->bufx)
	+ (((int)ft_strlen(&I->line[I->bufx]) % I->termw));
	nlines = I->nblines + autoc->nblines;
	ft_cursgoto(I->savecursx, I->savecursy, 1);
	if (I->savecursy + I->nblines > I->termh)
	{
		while (nlines--)
		{
			ft_putchar('\n');
			if (I->savecursy + I->nblines > I->termh)
				I->savecursy--;
		}
	}
	if (I->ret != CURSOR_O)
	{
		ft_cursgoto(I->savecursx, I->savecursy, 1);
		tputs((tgetstr("cd", NULL)), 0, ft_putc);
		ft_displaypromptline(I);
	}
}
