/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_special_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:16:06 by qrosa             #+#    #+#             */
/*   Updated: 2017/02/21 18:11:39 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_next_char(char *str, int i)
{
	int	pos;
	int	len_number;

	pos = 0;
	len_number = 0;
	if (str[i + 1] == '0' || str[i + 1] == 'x')
	{
		len_number = convert_hex_octal_to_char(str, i + 1);
		return (len_number);
	}
	while (pos < LEN_ECHO_SPECIAL_CHAR)
	{
		if (str[i + 1] == ECHO_SPECIAL_CHAR[pos])
		{
			if (pos == 9)
				return (-1);
			ft_putchar(ECHO_CONVERT_CHAR[pos]);
			return (1);
		}
		pos++;
	}
	ft_putchar('\\');
	return (0);
}

static bool	echo_print_special_str(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\\')
			ft_putchar(str[i]);
		else
		{
			if ((ret = check_next_char(str, i)) == -1)
				return (ERROR);
			i = i + ret;
		}
		i++;
	}
	return (SUCCESS);
}

bool		print_special_line(char **args, size_t len_tab,
									unsigned int tab_position, short options)
{
	while (tab_position < len_tab)
	{
		if (echo_print_special_str(args[tab_position]))
			return (ERROR);
		ft_putchar(' ');
		tab_position += 1;
	}
	if ((options & 2) != 2)
		ft_putchar('\n');
	return (SUCCESS);
}
