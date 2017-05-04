/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 20:28:07 by ljohan            #+#    #+#             */
/*   Updated: 2017/04/12 17:44:04 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# include <signal.h>
# include <termios.h>
# include <term.h>

# include <sys/stat.h>
# include <limits.h>

# include "libft.h"
# include "ft_printf.h"
# include "opt_parse_arg.h"

# include "list_head.h"
# include "jobs.h"
# include "parser.h"
# include "dict.h"
# include "options.h"
# include "states.h"
# include "debug.h"

# include "getline.h"
# include "autocomp.h"

# include "history.h"
# include "exec.h"
# include "builtins.h"

# ifdef __linux__
#  include <sys/wait.h>
#  include <sys/types.h>
#  include <time.h>
# endif

/*
** compil flags
*/

# ifndef FT_DEBUG
#  define FT_DEBUG	0
# endif

# ifndef FT_TEST
#  define FT_TEST	0
# endif

# define I 			input
# define SUCCESS	0
# define ERROR		1

struct			s_shell
{
	t_options	*options;
	t_history	*history;
	t_jobs		*bg_jobs;
	t_parser	*parser;
	char		script;

	int			status;
};

t_shell			*new_shell(t_options *opts);
void			destroy_shell(t_shell **shell);

/*
** ==================================================
** non range'
** ==================================================
*/

char			*ft_strjoinfree(char *s0, char *s1);
char			*ft_strjoin3(char *s0, char *s1, char *s2);

/*
** signals
*/

void			handle_sigint(int sig);

/*
** ft_path
*/

int				ft_charat(char *str, char c);
int				ft_rcharat(char *str, char c);
int				ft_isfile(char *path);
int				ft_isdir(char *path);
int				ft_exists(char *path);

char			*expand_user(const char *path, t_dict *env);

/*
** ft_stab
*/

char			**ft_stabnew(size_t size);
size_t			ft_stablen(char *const *stab);
char			**ft_stabdup(char *const *stab);
void			ft_stabdel(char ***stab);
int				ft_stabpush(char ***stab, char *entry);
int				ft_stabpop(char ***stab, size_t idx);
int				ft_stabupd(char ***stab, size_t idx,
					char *entry);
void			debug(int n, char *path);

/*
** script
*/

int				script_loop(t_shell *sh);

#endif
