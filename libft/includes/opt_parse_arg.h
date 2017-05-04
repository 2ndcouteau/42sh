/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_parse_arg.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 15:23:27 by qrosa             #+#    #+#             */
/*   Updated: 2017/02/22 16:45:53 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPT_PARSE_ARG_H
# define OPT_PARSE_ARG_H

# include "libft.h"
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>

/*
*******************
**	Get_Arg_Opt  **
*******************
** For use it, define *mytab[6] with name, options and error description in
** opt_init_env().
** Then, you have to call the fonction "opt_parse_arguments".
** See the Documentation for more details.
*/

typedef struct		s_bool
{
	bool			a;
}					t_bool;

typedef	struct		s_opt
{
	char			**define;
	int				position;
	char			*opt;
	char			*opt_all;
	char			*l_opt;
	int				nb_arg;
	char			**s_arg;
	char			bad_char;
	int				error;
	int				mark;
	struct s_bool	*opt_b;
}					t_opt;

/*
**	Define "mark" parameter
*/

# define ALL_OK			0
# define NO_OPT_OK		1
# define BAD_OPT		2
# define OPT_OK_END		3
# define NO_OPT_OK_END	4

/*
**	Define "error" parameter
*/

# define NO_ERROR		0
# define ERROR_MALLOC	1
# define BAD_SHORT_OPT	2
# define BAD_LONG_OPT	3

t_opt				*opt_parse_arguments(int argc, char **argv, char **init);
void				opt_get_options(int argc, char **argv, t_opt **e);
void				opt_init_env(t_opt **e, char **init_define);
bool				opt_is_valid(char *str, t_opt **e);
void				opt_exist_letter(char *str, t_opt **e, int i, int a);
bool				opt_exist_long(char *str, t_opt **e);
void				opt_save_arg(char *str, t_opt **e);
void				opt_check_options(t_opt **e);
void				opt_free(t_opt **e);
void				opt_print_error(char **argv, t_opt **e);
int					opt_check_last_opt(char *opt_all, char opt0, char opt1);

#endif
