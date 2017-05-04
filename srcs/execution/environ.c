/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 20:53:47 by ljohan            #+#    #+#             */
/*   Updated: 2017/04/25 20:53:18 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*ret;

	if (s3)
	{
		if (!(ret = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3))))
			return (NULL);
		ft_strcpy(ret, s1);
		ft_strcat(ret, s2);
		ft_strcat(ret, s3);
	}
	else
	{
		if (!(ret = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
			return (NULL);
		ft_strcpy(ret, s1);
		ft_strcat(ret, s2);
	}
	return (ret);
}

char	*ft_getenv(t_dict *env, char *key)
{
	t_cell	*ptr;

	if (!env)
		return (NULL);
	ptr = dict_get(env, key);
	if (ptr && ptr->value)
		return (ptr->value);
	return (NULL);
}

int		ft_setenv(t_dict *env, char *key, char *new_value)
{
	t_cell	*cell;

	if ((new_value && ((cell = new_cell(
		ft_strdup(key), ft_strdup(new_value), &del_str_value)) == NULL
		|| cell->key == NULL))
	|| (!new_value && ((cell = new_cell(
		ft_strdup(key), ft_strnew(0), &del_str_value)) == NULL
	|| cell->key == NULL)))
	{
		del_cell(&cell);
		return (1);
	}
	dict_set(env, cell);
	return (0);
}

int		ft_unsetenv(t_dict *env, char *key)
{
	t_cell	*ptr;

	if (!(ptr = dict_get(env, key)))
		return (1);
	if (ptr)
		dict_del(env, key);
	return (0);
}
