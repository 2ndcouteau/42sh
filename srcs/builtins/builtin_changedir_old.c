/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_changedir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:01:44 by amoreilh          #+#    #+#             */
/*   Updated: 2017/01/23 15:01:46 by amoreilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/param.h>

static int	ft_checkcderr(char *path)
{
	struct stat b;

	if ((stat(path, &b) >= 0) && (S_ISDIR(b.st_mode)) && (b.st_mode & S_IXUSR))
		return (0);
	else
	{
		if ((stat(path, &b) < 0))
			ft_printf("cd : No such file or directory : %s", path);
		else if (!(S_ISDIR(b.st_mode)))
			ft_printf("cd : Not a directory : %s", path);
		else if (!(b.st_mode & S_IXUSR))
			ft_printf("cd : Permission denied : %s", path);
	}
	return (1);
}

static int	ft_changedirarg(char *path, char *currentdir, t_dict *env)
{
	int		ret;
	char	*newdir;
	char	cwdbuf[MAXPATHLEN + 1];

	ret = 1;
	if (ft_strequ(path, "-"))
	{
		newdir =
		(newdir = ft_getenv(env, "OLDPWD")) ? ft_strdup(newdir) : NULL;
		if ((ret = chdir(newdir)) == 0)
		{
			ft_setenv(env, "OLDPWD", currentdir);
			ft_setenv(env, "PWD", newdir);
		}
		free(newdir);
	}
	else if (!ft_checkcderr(path) && (newdir = path))
		if ((ret = chdir(newdir)) == 0)
		{
			newdir = getcwd(cwdbuf, MAXPATHLEN);
			ft_setenv(env, "OLDPWD", currentdir);
			ft_setenv(env, "PWD", newdir);
		}
	return (ret);
}

int			ft_cd(char **cmds, t_dict *env)
{
	char	*currentdir;
	char	*newdir;
	char	cwdbuf[MAXPATHLEN + 1];
	int		ret;

	ret = 1;
	currentdir = ft_strdup(getcwd(cwdbuf, MAXPATHLEN));
	if (cmds[1])
		ret = ft_changedirarg(cmds[1], currentdir, env);
	if (!cmds[1])
	{
		newdir = ft_getenv(env, "HOME");
		if (newdir && (ret = chdir(newdir)) == 0)
		{
			ft_setenv(env, "OLDPWD", currentdir);
			ft_setenv(env, "PWD", newdir);
		}
	}
	free(currentdir);
	return (ret);
}
