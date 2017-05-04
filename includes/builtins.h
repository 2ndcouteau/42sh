/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 19:54:52 by nboulaye          #+#    #+#             */
/*   Updated: 2017/02/24 20:44:39 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"

# define __BUILTIN_CD			1
# define __BUILTIN_ENV			2
# define __BUILTIN_SETENV		3
# define __BUILTIN_UNSETENV		4
# define __BUILTIN_BG			20
# define __BUILTIN_FG			21
# define __BUILTIN_JOBS			22
# define __BUILTIN_HELP			10
# define __BUILTIN_EXIT			11
# define __BUILTIN_ECHO			12
# define __BUILTIN_ALIAS  		13
# define __BUILTIN_UNALIAS  	14
# define __BUILTIN_SET  		15
# define __BUILTIN_UNSET  		16
# define __BUILTIN_HISTORY		30

# define LEN_ECHO_SPECIAL_CHAR	10
# define ECHO_SPECIAL_CHAR		"\\abefnrtvc"
# define ECHO_CONVERT_CHAR		"\\\a\b\e\f\n\r\t\v"

# define SUCCESS				0
# define ERROR					1

typedef struct	s_help
{
	char		*name;
	char		*help;
	char		*doc;
}				t_help;

/*
**	Current Command
*/
typedef struct	s_cmd
{
	char		**split_line;
	size_t		size_split_line;
	size_t		error_nbr;
	char		*error_name;
}				t_cmd;

int				ft_help(char **args);
t_help			*new_help(char *name, char *help, char *doc);
int				check_varname_format(char *varname);

void			help_set_help(t_dict *help);
void			help_set_env(t_dict *help);
void			help_set_setenv(t_dict *help);
void			help_set_unsetenv(t_dict *help);
void			help_set_jobs(t_dict *help);
void			help_set_fg(t_dict *help);
void			help_set_bg(t_dict *help);
void			help_set_alias(t_dict *help);
void			help_set_unalias(t_dict *help);
void			help_set_set(t_dict *help);
void			help_set_unset(t_dict *help);
void			help_set_history(t_dict *help);
void			help_set_echo(t_dict *help);
void			help_set_cd(t_dict *help);

int				builtin_history(t_shell *shell, char **argv);
int				builtin_history_print(char **tab_arg, t_history *h, int i);
int				builtin_jobs(t_jobs **bg_jobs, char **argv);
int				builtin_fg(t_jobs **bg_jobs, char **argv);
int				builtin_bg(t_jobs **bg_jobs, char **argv);
int				read_arg_env(t_processes *proc, int *idx
				, t_dict **modif_env, int flag);
int				builtin_env(t_jobs **jobs, t_processes *proc, t_shell *sh);
t_dict			*print_env(t_dict **env);
int				builtin_setenv(t_processes *proc, t_shell *sh);
int				builtin_unsetenv(t_processes *proc, t_shell *sh);
int				ft_exit(t_shell *sh, t_processes *proc);
int				builtin_echo(char **args);
int				builtin_alias(t_shell *shell, char **args);
int				builtin_unalias(t_shell *shell, char **args);
int				builtin_set(t_shell *shell, char **args);
int				builtin_unset(t_shell *shell, char **args);
int				ft_cd(char **cmds, t_dict *env);

/*
**	Echo Builtins Functions
*/
void			print_echo_line(char **args, size_t len_tab,
	unsigned int tab_position, short options);
void			print_direct_line(char **args, size_t len_tab,
	unsigned int tab_position, short options);
bool			print_special_line(char **args, size_t len_tab,
	unsigned int tab_position, short options);
bool			print_long_options(short options);
short			check_option_echo(char **args, size_t len_tab, short *options);
void			set_option(char *word, short *options);
bool			is_valid_option(char *word, int size_tab);
int				convert_hex_octal_to_char(char *str, int i);

/*
**	CD Builtins Functions
*/
void			cd_create_path_name(t_cmd *current_cmd, t_dict *e,
					t_opt **cd_opt, char **current_pwd);
bool			cd_check_valid_file(t_cmd *current_cmd,
					char **current_pwd, char *name);
void			cd_set_error(t_cmd *current_cmd, char *name, int nbr);
int				cd_check_new_path(char *new_path);
void			cd_oldpwd(t_cmd *current_cmd, t_dict *e, char **current_pwd);
void			cd_home(t_cmd *current_cmd, t_dict *e,
					char **current_pwd, char *new_path);
void			cd_relative_path(t_cmd *current_cmd,
					char **current_pwd, char *new_path);
void			cd_absolute_path(t_cmd *current_cmd,
					char **current_pwd, char *new_path);
void			cd_swap_pwd_env(t_dict *e, char **current_pwd, t_opt **cd_opt);
void			cd_clean_path(char **current_pwd);
bool			cd_add_end_path(char **current_pwd, char *add_elem,
					int pwd_len);
void			cd_print_error(int error, char *name);
char			cd_check_typefile(mode_t mode);

#endif
