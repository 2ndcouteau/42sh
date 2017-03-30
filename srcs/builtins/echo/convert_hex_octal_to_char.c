/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_hex_octal_to_char.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 18:24:54 by qrosa             #+#    #+#             */
/*   Updated: 2017/02/21 18:01:11 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			convert_hextodecimal(char symbol)
{
	if (ft_isdigit(symbol))
		return (symbol - 48);
	if (symbol > 64 && symbol < 71)
		return (symbol - 55);
	if (symbol > 96 && symbol < 103)
		return (symbol - 87);
	return (-1);
}

int			print_hexa_char(char *str, int i)
{
	int	decimal_char_value;
	int	tmp;

	if ((tmp = convert_hextodecimal(str[i])) != -1)
	{
		if ((decimal_char_value = convert_hextodecimal(str[i + 1])) != -1)
		{
			decimal_char_value += (tmp * 16);
			ft_putchar(decimal_char_value);
			return (2);
		}
		ft_putchar(tmp);
		return (1);
	}
	return (0);
}

static int	convert_octtodecimal(char symbol)
{
	if (symbol > 47 && symbol < 56)
		return (symbol - 48);
	return (-1);
}

static int	print_octal_char(char *str, int i)
{
	int	decimal_char_value;
	int	tmp1;
	int	tmp2;

	if ((tmp1 = convert_octtodecimal(str[i])) != -1)
	{
		if ((tmp2 = convert_octtodecimal(str[i + 1])) != -1)
		{
			if ((decimal_char_value = convert_octtodecimal(str[i + 2])) != -1)
			{
				decimal_char_value += (tmp1 * 8 * 8) + (tmp2 * 8);
				ft_putchar(decimal_char_value);
				return (3);
			}
			tmp2 += (tmp1 * 8);
			ft_putchar(tmp2);
			return (2);
		}
		ft_putchar(tmp1);
		return (1);
	}
	return (0);
}

int			convert_hex_octal_to_char(char *str, int i)
{
	int	len_number;

	len_number = 1;
	if (str[i] == 'x')
		len_number += print_hexa_char(str, i + 1);
	else
		len_number += print_octal_char(str, i + 1);
	return (len_number);
}
