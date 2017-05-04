/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main_transition.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:15:48 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/28 22:57:25 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	transition_suite(t_shell *shell, t_parser *p)
{
	if (STATE(p) == ST_EOF)
		return (transition_eof(p));
	else if (STATE(p) == ST_PIPE)
		return (transition_pipe(p));
	else if (STATE(p) == ST_EOC)
		return (transition_eoc(p));
	else if (STATE(p) == ST_ESCAPE)
		return (transition_escape(p));
	else if (STATE(p) == ST_ONELINE)
		return (1);
	else if (STATE(p) == ST_HEREDOC)
		return (transition_heredoc(p));
	else if (STATE(p) == ST_SUBSHELL)
		return (transition_subshell(shell, p));
	else
		return (transition_error(p));
	return (1);
}

char		transition(t_shell *shell, t_parser *p)
{
	if (STATE(p) == ST_PASS)
	{
		pop_state(&(p->states));
		return (0);
	}
	if (STATE(p) == ST_NORM)
		return (transition_normal(p));
	else if (STATE(p) == ST_ONEMORE)
		return (transition_onemore(p));
	else if (STATE(p) == ST_STR)
		return (transition_string(p));
	else if (STATE(p) == ST_QUOTE)
		return (transition_quote(p));
	else if (STATE(p) == ST_REDIR)
		return (transition_bg(p));
	else if (STATE(p) == ST_BG)
		return (transition_bg(p));
	else if (STATE(p) == ST_VAR)
		return (transition_var(p));
	else if (STATE(p) == ST_PATH)
		return (transition_path(p));
	else
		return (transition_suite(shell, p));
}
