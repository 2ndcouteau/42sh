/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_option_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:22:34 by qrosa             #+#    #+#             */
/*   Updated: 2017/02/21 18:00:59 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	set_short_options(char *word, short *options)
{
	int i;

	i = 1;
	while (word[i] != '\0')
	{
		if (word[i] == 'E')
		{
			if ((*options & 1) == 1)
				*options -= 1;
		}
		else if (word[i] == 'e')
		{
			if ((*options & 1) != 1)
				*options += 1;
		}
		else
		{
			if ((*options & 2) != 2)
				*options += 2;
		}
		i++;
	}
}

static void	set_long_options(char *word, short *options)
{
	if (word[2] == 'h')
		*options += 4;
	else
		*options += 8;
}

void		set_option(char *word, short *options)
{
	if (word[1] == '-')
		set_long_options(word, options);
	else
		set_short_options(word, options);
}
