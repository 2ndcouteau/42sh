/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 20:53:47 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/10 19:48:31 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	init_shlvl(t_dict *env)
{
	char	*ptr;
	char	*shlvl_str;

	if ((ptr = ft_getenv(env, "SHLVL")))
	{
		shlvl_str = ft_itoa(ft_atoi(ptr) + 1);
		ft_setenv(env, "SHLVL", shlvl_str);
		ft_memdel((void **)&shlvl_str);
	}
	else
		ft_setenv(env, "SHLVL", "1");
}

t_options	*new_options(int ac, char **av, char **env)
{
	t_options	*opts;

	if ((opts = (t_options*)ft_memalloc(sizeof(t_options))) == NULL)
		return (NULL);
	if (ac > 1 && ft_isfile(av[1]) > 0)
		opts->fd = open(av[1], O_RDONLY);
	else
		opts->fd = STDIN_FILENO;
	opts->env = env2dict(env);
	init_shlvl(opts->env);
	if (opts->fd < 0)
		destroy_options(&opts);
	if (isatty(opts->fd))
		if (tcgetattr(opts->fd, &opts->term))
		{
			ft_putstr_fd("\033[31mValid TERM var needed\033[0m\n", 2);
			exit(1);
		}
	if ((opts->vars = new_dict(32)) == NULL)
		destroy_options(&opts);
	if ((opts->aliases = new_dict(1)) == NULL)
		destroy_options(&opts);
	return (opts);
}

void		destroy_options(t_options **opts)
{
	if (*opts == NULL)
		return ;
	if ((*opts)->env != NULL)
		destroy_dict(&(*opts)->env);
	if ((*opts)->vars != NULL)
		destroy_dict(&(*opts)->vars);
	if ((*opts)->bins != NULL)
		destroy_dict(&(*opts)->bins);
	if ((*opts)->aliases != NULL)
		destroy_dict(&(*opts)->aliases);
	close((*opts)->fd);
	ft_memdel((void **)&*opts);
	(*opts) = NULL;
}
