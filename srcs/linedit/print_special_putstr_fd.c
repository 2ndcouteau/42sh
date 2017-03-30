/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_special_putstr_fd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 19:05:43 by qrosa             #+#    #+#             */
/*   Updated: 2017/03/27 19:09:42 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_special_putstr_fd(char *str, int fd)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(str);
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '\n')
			tmp[i] = ' ';
		i++;
	}
	ft_putstr_fd(tmp, fd);
	tmp = ft_free_line(&tmp);
}
