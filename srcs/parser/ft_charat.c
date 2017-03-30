/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 12:35:03 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/20 16:48:44 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_charat(char *str, char c)
{
	char	*ptr;

	if ((ptr = ft_strchr(str, c)) == NULL)
		return (-1);
	return (ptr - str);
}

int		ft_rcharat(char *str, char c)
{
	char	*ptr;

	if ((ptr = ft_strrchr(str, c)) == NULL)
		return (-1);
	return (ptr - str);
}
