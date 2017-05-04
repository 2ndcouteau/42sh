/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 12:13:42 by ljohan            #+#    #+#             */
/*   Updated: 2017/04/27 23:04:43 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "list_head.h"
# include "states.h"
# include "jobs.h"
# include "dict.h"
# include "options.h"

typedef struct	s_parser
{
	char		*orig;
	int			idx;
	char		*part;
	t_options	*opts;
	t_states	*states;
	t_cmds		*last_cmd;
	t_jobs		*jobs;
	char		first_word;
	char		*errmess;
	char		eof;
	char		merge;
	char		aliases_done;
}				t_parser;

# define CURRENT(parser) (&(parser->orig[parser->idx]))

enum {
	ST_NORM,
	ST_STR,
	ST_MULTILINE,
	ST_ONELINE,
	ST_VAR,
	ST_PATH,
	ST_AND,
	ST_OR,
	ST_ESCAPE,
	ST_BG,
	ST_REDIR,
	ST_PIPE,
	ST_EOC,
	ST_EOF,
	ST_ERR,
	ST_HEREDOC,
	ST_PASS,
	ST_SETVAR,
	ST_QUOTE,
	ST_SUBSHELL,
	ST_ONEMORE,
};

# define ST_INIT ST_NORM
# define STATE(p) (p->states == NULL ? -1 : p->states->state)
# define PRE_IS_ML(p) (STATE(p) == ST_MULTILINE) || (STATE(p) == ST_ONELINE)
# define IS_ML(p) PRE_IS_ML(p) || (STATE(p) == ST_HEREDOC)

/*
** charsets
*/

# define CS_BLANK " \t\n"
# define CS_ESCAPE " \t\n$\"\\;~|&<>='`"
# define CS_ESCAPE_STR "$\"\\`"
# define CS_ESCAPE_VAR "\\ \"\t;$~/|<>"
# define CS_ESCAPE_PATH "\\ \"\t;$~|<>"
# define CS_REDIR "0123456789><&"
# define CS_SUBSHELL "\\`"

# define IS_BLANK(c) (ft_strchr(CS_BLANK, c) != NULL)
# define IS_EOC(c) (c == 0 || ft_strchr(";|&", c) != NULL)

/*
** struct_options
*/

void			destroy_options(t_options **opts);
t_options		*new_options(int ac, char **av, char **env);

/*
** struct_parser
*/

t_parser		*new_parser(t_options *opts);
void			destroy_parser(t_parser **parser);
int				reset_parser(t_parser **parser);

/*
** parse line
*/

char			*forward_with(char *str, const char *charset);
char			*forward_escape(char *str, const char *charset);

# define FWD(s) forward_escape(s, CS_ESCAPE)
# define FWD_STR(s) forward_escape(s, CS_ESCAPE_STR)
# define FWD_VAR(s) forward_escape(s, CS_ESCAPE_VAR)
# define FWD_PATH(s) forward_escape(s, CS_ESCAPE_PATH)
# define FWD_REDIR(s) forward_with(s, CS_REDIR)

/*
** main
*/

void			action(t_shell *sh);
char			*implicit_parse_one(t_shell *sh, t_parser *p);

/*
** normal.c
*/

char			*parse_normal(t_parser *parser);
char			*handle_normal(t_shell *sh, t_parser *p);
char			*handle_onemore(t_shell *sh, t_parser *p);

/*
** first_word.c
*/

char			*handle_first_word(t_shell *sh, t_parser *p);

/*
** path utils
*/

char			*ft_joinpath(const char *p0, const char *p1);
char			*parse_path(t_parser *p, t_dict *env);

/*
** parse utils
*/

void			merge_part(t_parser *p);
void			update_part(t_parser *p, char *part);

/*
** handlers.c
** may change
*/

void			void_handler(t_parser *p);
void			handle_error(t_parser *p);
void			handle_eof(t_parser *p);
void			handle_eoc(t_parser *p);
void			handle_setvar(t_shell *shell, t_parser *p);
void			handle_pipe(t_parser *p);
void			handle_heredoc(t_parser *p);

/*
** transitions.c
*/

char			transition(t_shell *shell, t_parser *p);
int				transition_normal(t_parser *p);
int				transition_eof(t_parser *p);
int				transition_eoc(t_parser *p);
int				transition_pipe(t_parser *p);
int				transition_escape(t_parser *p);
int				transition_string(t_parser *p);
int				transition_quote(t_parser *p);
int				transition_heredoc(t_parser *p);
int				transition_error(t_parser *p);
int				transition_bg(t_parser *p);
int				transition_var(t_parser *p);
int				transition_path(t_parser *p);
int				transition_subshell(t_shell *shell, t_parser *p);
int				transition_onemore(t_parser *p);

/*
** parse.c
*/

char			*parse_quote(t_parser *p);
char			*parse_string(t_parser *p);
char			*parse_subshell(t_parser *p);
char			*parse_var(t_parser *p);
char			*parse_escape(t_parser *p);
char			*parse_oneline(t_parser *p);
char			*parse_bg(t_parser *p);

/*
** parse_redir*
*/

char			*get_red_fdout(t_parser *p, int *idx);
char			*get_left_redir(t_parser *p, int *idx);
char			*human_redtype(int redtype);
int				get_rtype(t_parser *p, int *idx);
void			destroy_redir(t_redir **red);

/*
** // others
*/

void			merge_redir(t_parser *p, t_redir *red);

void			parse(t_shell *shell, char stop);
t_redir			*get_current_redir(t_parser *p);
char			*ft_stabjoin(char *sep, char **stab);
t_redir			*try_redir(t_shell *sh, t_parser *p);
void			handle_aliases(t_parser *p, char *key, char *alias);
char			*ft_eval(t_shell *shell, char *code);

int				itab_push(int ***itab, int i0, int i1);
size_t			itab_len(int **itab);
void			itab_del(int ***itab);

#endif
