/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:15:48 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/23 17:30:46 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*handle_continue(t_parser *p)
{
	pop_state(&(p->states));
	if (STATE(p) == ST_REDIR)
	{
		ft_printf("Continue REDIR\n");
	}
	return (NULL);
}

static void	action_suite(t_parser *p)
{
	if (STATE(p) == ST_EOF)
		handle_eof(p);
	else if (STATE(p) == ST_PIPE)
		handle_pipe(p);
	else if (STATE(p) == ST_BG)
		update_part(p, parse_bg(p));
	else if (STATE(p) == ST_ONELINE)
		update_part(p, parse_oneline(p));
	else if (STATE(p) == ST_HEREDOC)
		handle_heredoc(p);
	else if (STATE(p) == ST_SETVAR)
		handle_setvar(p);
	else if (STATE(p) == ST_CONTINUE)
		update_part(p, handle_continue(p));
	else if (STATE(p) == ST_SUBSHELL)
		update_part(p, parse_subshell(p));
	else
		handle_error(p);
}

void		action(t_shell *sh)
{
	if (STATE(sh->parser) == ST_NORM || STATE(sh->parser) == ST_REDIR)
		update_part(sh->parser, handle_normal(sh, sh->parser));
	else if (STATE(sh->parser) == ST_STR)
		update_part(sh->parser, parse_string(sh->parser));
	else if (STATE(sh->parser) == ST_QUOTE)
		update_part(sh->parser, parse_quote(sh->parser));
	//else if (STATE(sh->parser) == ST_POSTPIPE)
//		update_part(sh->parser, parse_postpipe(sh->parser));
	else if (STATE(sh->parser) == ST_VAR)
		update_part(sh->parser, parse_var(sh->parser));
	else if (STATE(sh->parser) == ST_PATH)
		update_part(sh->parser, parse_path(sh->parser));
	else if (STATE(sh->parser) == ST_EOC)
		handle_eoc(sh->parser);
	else if (STATE(sh->parser) == ST_ESCAPE)
		update_part(sh->parser, parse_escape(sh->parser));
	else
		action_suite(sh->parser);
}

void		parse(t_shell *shell)
{
	char	stop;

	stop = 0;
	while (!stop && shell->parser->orig != NULL)
	{
		(g_debug[0]) ? debug_parser(shell->parser) : 1;
		action(shell);
		stop = transition(shell, shell->parser);
	}
	if (g_debug[0])
	{
		ft_fdprintf(g_debug[1], "\x1b[32mFinal:\x1b[0m\n");
		debug_parser(shell->parser);
		ft_fdprintf(g_debug[1], "\x1b[36m === END ===\x1b[0m\n");
	}
	if (shell->parser->eof)
	{
		shell->parser->eof = 0;
		if (STATE(shell->parser) == ST_MULTILINE
		&& GET_NODE(shell->parser->states->head.next, t_states, head)->state
		== ST_STR)
		{
			ft_fdprintf(2, "\nparse error: unexpected eof.");
			push_state(&(shell->parser->states), ST_ERR);
		}
		else
		{
			pop_state(&(shell->parser->states));
			return (parse(shell));
		}
	}
}