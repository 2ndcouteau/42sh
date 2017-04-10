/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_firstletters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoko <yoko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 13:45:28 by yoko              #+#    #+#             */
/*   Updated: 2017/04/09 18:12:08 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			*comp_firstletters(t_input *input)
{
	int		pos;
	char	*str;

	pos = I->bufpos;
	if (pos >= I->prompt2len && ft_isspace(I->line[pos]) &&
	(!ft_isspace(I->line[pos - 1])))
		pos--;
	while (!ft_isspace(I->line[pos]) && pos >= I->prompt2len)
		pos--;
	if (ft_isspace(I->line[pos]) && (!ft_isspace(I->line[pos + 1])))
		pos++;
	if ((str = ft_strsub(I->line, pos, ft_abs(I->bufpos - pos))))
		return (str);
	else
		return (NULL);
}
