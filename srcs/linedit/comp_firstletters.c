/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_firstletters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoko <yoko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 13:45:28 by yoko              #+#    #+#             */
/*   Updated: 2017/03/23 17:17:55 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// This function check what is the first letter of the last word  ???
char			*comp_firstletters(t_input *input)
{
	int		pos;
	char	*str;

	pos = I->bufpos;
	if (pos >= I->prompt2len && ft_isspace(I->line[pos]) &&
	(!ft_isspace(I->line[pos - 1])))	// Pos >= ?? I->prompt2len // What happen if (pos == I->prompt2len): You check two characters of the prompt..
		pos--;
	while (!ft_isspace(I->line[pos]) && pos >= I->prompt2len)		// go back in the line to the previous letter before the start of the current word
		pos--;
	if (ft_isspace(I->line[pos]) && (!ft_isspace(I->line[pos + 1]))) // advance to the first letter of the current word
		pos++;
	if ((str = ft_strsub(I->line, pos, abs(I->bufpos - pos)))) // why need absolute value? Can it be a negative value? really ?
		return (str);	// return a word.
	else
		return (NULL);
}
