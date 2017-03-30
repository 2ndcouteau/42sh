/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 12:57:47 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/05 21:49:02 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

typedef struct		s_options
{
	int				fd;
	t_dict			*env;
	t_dict			*vars;
	t_dict			*bins;
	t_dict			*aliases;
	struct termios	term;
}					t_options;

# define _SIZE_ENV_DICT	32

# define _FLAG_I		2
# define _FLAG_N		2
# define _FLAG_U		4
# define _FLAG_E		4
# define _FLAG_C		8
# define _FLAG_D		0x10

t_dict				*init_env(char **env_o);
char				*ft_getenv(t_dict *env, char *key);
int					ft_setenv(t_dict *env, char *key, char *new_value);
int					ft_unsetenv(t_dict *env, char *key);

#endif
