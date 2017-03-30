/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 12:38:37 by ljohan            #+#    #+#             */
/*   Updated: 2016/11/07 13:22:27 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_exists(char *path)
{
	struct stat st;

	return (stat(path, &st) != -1);
}

int		ft_isdir(char *path)
{
	struct stat st;

	if (stat(path, &st) == -1)
		return (-1);
	return (S_ISDIR(st.st_mode));
}

int		ft_isfile(char *path)
{
	struct stat st;

	if (stat(path, &st) == -1)
		return (-1);
	return (S_ISREG(st.st_mode));
}

char	*ft_basename(char *path)
{
	size_t	len;
	int		i;

	len = ft_strlen(path);
	if (!len)
		return (ft_strnew(0));
	if (path[len - 1] == '/')
		i = len - 1;
	else
		i = ft_rcharat(path, '/');
	if (i == -1)
		return (ft_strdup(path));
	i++;
	return (ft_strsub(path, i, len - i));
}

char	*ft_dirname(char *path)
{
	size_t	len;
	int		i;

	len = ft_strlen(path);
	if (!len)
		return (ft_strnew(0));
	i = ft_rcharat(path, '/');
	if (i == -1)
		return (ft_strnew(0));
	return (ft_strsub(path, 0, i));
}
