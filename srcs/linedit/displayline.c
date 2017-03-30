/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 15:42:42 by amoreilh          #+#    #+#             */
/*   Updated: 2017/03/27 19:08:10 by qrosa            ###   ########.fr       */
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


/*
 	Need to split this function in two parts:
		One for print the prompt.
			Call this print_prompt() in the get_loop() juste before the endless_loop
		Second who print the line, and just the right part of the line
*/

// The Original Function.
//
// void	ft_displaypromptline(t_input *input)
// {
// 	int arrowindex;
// 	int i;
//
// 	i = 0;
// 	arrowindex = ft_strlen(I->prompt2)
// 		- (ft_strlen((ft_strrchr(I->prompt2, '>'))));
// 	if (!I->prompt)
// 		while (i++ < arrowindex)
// 			write(2, " ", 1);
// 	else
// 		ft_putnstr_fd(I->line, arrowindex, 2);
// 	ft_putstr_fd("\033[38;5;208m", 2);
// 	ft_putnstr_fd(&I->line[arrowindex], 1, 2);
// 	if (ft_strchr(I->line, '\n'))
// 	{
// 		ft_putstr_fd("\033[38;5;240m", 2);
// 		ft_putstr_fd(&I->line[arrowindex + 1], 2);
// 		ft_putstr_fd("\033[0m", 2);
// 	}
// 	else if (!ft_strchr(I->line, '\n'))
// 	{
// 		ft_putstr_fd("\033[0m", 2);
// 		ft_putstr_fd(&I->line[arrowindex + 1], 2);
// 	}
// 	(I->end || I->comp) ? ft_putchar('\n') : 1;
// }

// void	print_prompt(t_input *input)
// {
// 	int arrowindex;
// 	int i;
//
// 	i = 0;
// 	arrowindex = ft_strlen(I->prompt2)
// 		- (ft_strlen((ft_strrchr(I->prompt2, '>'))));
// 	if (!I->prompt)
// 		while (i++ < arrowindex)
// 			write(2, " ", 1);
// 	else
// 		ft_putnstr_fd(I->line, arrowindex, 2);
// 	ft_putstr_fd("\033[38;5;208m", 2);
// 	ft_putnstr_fd(&I->line[arrowindex], 1, 2);
// }
//
// // This function need to be adapted for print one or several letter as in Paste.
//
// 		// Do not print when you just Cut part of line. Ctrl+k or Ctrl+u
// void	ft_displaypromptline(t_input *input)
// {
// 	int arrowindex;
//
// 	if (ft_strchr(I->line, '\n'))
// 	{
// 		arrowindex = ft_strlen(I->prompt2)
// 			- (ft_strlen((ft_strrchr(I->prompt2, '>'))));
// 		ft_putstr_fd("\033[38;5;240m", 2);				// print the line if it's history
// 		ft_putstr_fd(&I->line[arrowindex + 1], 2);
// 		ft_putstr_fd("\033[0m", 2);
// 	}
// 	else
// 	{
// 		ft_putstr_fd("\033[0m", 2);
// 		ft_putstr_fd(&I->line[I->bufpos - 1], 2);					// Why writing on error output ?
// 	}
// 	(I->end || I->comp) ? ft_putchar('\n') : 1;			// add a jump line if it is an execution
// }
//
//
// void	ft_printbuf(t_input *input, t_autocomp *autoc)
// {
// 	int nlines;
//
// 	I->bufposmax = ft_strlen(I->line);
// 	I->nblines = ft_nblines(I);
// 	I->bufy = (I->bufpos / I->termw);
// 	I->bufx = (I->bufpos - (I->termw * I->bufy));
// 	I->bufxmax = (I->bufx)
// 	+ (((int)ft_strlen(&I->line[I->bufx]) % I->termw));
// 	nlines = I->nblines + autoc->nblines;
// 	// ft_cursgoto(I->savecursx, I->savecursy, 1);
// 	// if (I->savecursy + I->nblines > I->termh)
// 	// {
// 	// 	while (nlines--)
// 	// 	{
// 	// 		ft_putchar('\n');
// 	// 		if (I->savecursy + I->nblines > I->termh)
// 	// 			I->savecursy--;
// 	// 	}
// 	// }
// 	if (I->ret != CURSOR_O)
// 	{
// 		//ft_cursgoto(I->savecursx, I->savecursy, 1);
// 		put_stdout("cd");	// check return plz;
// 		ft_displaypromptline(I);
// 	}
// }



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
	ft_putnstr_fd(&I->line[arrowindex], 1, 2);		// print orange arrow

	if (ft_strchr(I->line, '\n'))
	{
		ft_putstr_fd("\033[38;5;240m", 2);
		print_special_putstr_fd(&I->line[arrowindex + 1], 2);
		// ft_putstr_fd(&I->line[arrowindex + 1], 2);
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
		// printf("\nbufpos == %d\nbufposmax ==  %d\nbuffsize == %d\n", I->bufpos, I->bufposmax, I->buffsize);
		ft_cursgoto(I->savecursx, I->savecursy, 1);
		tputs((tgetstr("cd", NULL)), 0, ft_putc);
		ft_displaypromptline(I);
	}
}
