/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:23:26 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/06 21:29:00 by nboulaye         ###   ########.fr       */
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
	free(tmp);
	return (ret);
}

char	*expand_user(const char *path)
{
	char	*home;

	if (ft_strlen(path) == 0)
		return (ft_strnew(0));
	if (path[0] != '~')
		return (ft_strdup(path));
	if ((home = getenv("HOME")) != NULL)//////// bou gentenv!
	{
		home = ft_joinpath(home, path + 1);
		if (ft_exists(home))
			return (home);
		else
		{
			free(home);
			return (ft_strdup(path));
		}
	}
	return (NULL);
}

char	*parse_path(t_parser *p)
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
	if ((tmp = expand_user(path)) != NULL)
	{
		ft_strdel(&path);
		return (tmp);
	}
	return (path);
}