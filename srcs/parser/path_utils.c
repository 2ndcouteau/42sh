/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:23:26 by ljohan            #+#    #+#             */
/*   Updated: 2017/04/10 17:15:07 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_joinpath(const char *p0, const char *p1)
{
	char	*tmp;
	char	*ret;
	int		l0;

	l0 = (int)ft_strlen(p0);
	if (p0[l0 - 1] != '/')
		tmp = ft_strjoin(p0, "/");
	else
		tmp = ft_strdup(p0);
	while (p1[0] == '/')
		p1++;
	ret = ft_strjoin(tmp, p1);
	ft_memdel((void **)&tmp);
	return (ret);
}

char	*expand_user(const char *path, t_dict *env)
{
	char	*home;

	if (ft_strlen(path) == 0)
		return (ft_strnew(0));
	if (path[0] != '~')
		return (ft_strdup(path));
	if ((home = ft_getenv(env, "HOME")) != NULL)
	{
		home = ft_joinpath(home, path + 1);
		if (ft_exists(home))
			return (home);
		else
		{
			ft_memdel((void **)&home);
			return (ft_strdup(path));
		}
	}
	return (NULL);
}

char	*parse_path(t_parser *p, t_dict *env)
{
	char	*path;
	char	*tmp;
	int		tst;

	tst = p->idx > 0 && !IS_BLANK(p->orig[p->idx - 1]);
	tmp = FWD_PATH(&CURRENT(p)[1]);
	if ((path = ft_strsub(p->orig, p->idx, tmp - CURRENT(p))) == NULL)
	{
		p->idx++;
		return (NULL);
	}
	p->idx += ft_strlen(path);
	if (tst)
		return (path);
	if ((tmp = expand_user(path, env)) != NULL)
	{
		ft_strdel(&path);
		return (tmp);
	}
	return (path);
}
