/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_option_is_valid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:20:10 by qrosa             #+#    #+#             */
/*   Updated: 2017/02/21 18:00:49 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	long_option_check(char *word)
{
	if (word[2] == 'h')
	{
		if (!ft_strncmp(word, "--help", 6))
			return (SUCCESS);
	}
	else if (word[2] == 'v')
	{
		if (!ft_strncmp(word, "--version", 9))
			return (SUCCESS);
	}
	return (ERROR);
}

static bool	short_option_check(char *word)
{
	int i;

	i = 1;
	while (word[i] != '\0')
	{
		if (word[i] == 'n' || word[i] == 'e' || word[i] == 'E')
			i++;
		else
			return (ERROR);
	}
	return (SUCCESS);
}

bool		is_valid_option(char *word, int size_tab)
{
	if (word[0] == '\0' || word[0] != '-')
		return (ERROR);
	else if (word[1] == '-')
	{
		if (size_tab == 2 && !long_option_check(word))
			return (SUCCESS);
	}
	else if (word[1] != '\0')
	{
		if (!short_option_check(word))
			return (SUCCESS);
	}
	return (ERROR);
}
