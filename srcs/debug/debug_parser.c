/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:51:13 by ljohan            #+#    #+#             */
/*   Updated: 2017/04/12 17:04:19 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*human_state_suite(int state)
{
	if (state == ST_EOF)
		return ("eof");
	else if (state == ST_ERR)
		return ("error");
	else if (state == ST_PIPE)
		return ("pipe");
	else if (state == ST_ONELINE)
		return ("oneline");
	else if (state == ST_SUBSHELL)
		return ("subshell");
	else if (state == ST_REDIR)
		return ("redir");
	else if (state == ST_HEREDOC)
		return ("heredoc");
	else if (state == ST_SETVAR)
		return ("setvar");
	else if (state == ST_QUOTE)
		return ("quote");
	else
		return ("unreconized");
}

char		*human_state(int state)
{
	if (state == ST_NORM)
		return ("normal");
	else if (state == ST_STR)
		return ("string");
	else if (state == ST_VAR)
		return ("var");
	else if (state == ST_OR)
		return ("or");
	else if (state == ST_BG)
		return ("bg");
	else if (state == ST_AND)
		return ("and");
	else if (state == ST_PATH)
		return ("path");
	else if (state == ST_ESCAPE)
		return ("escape");
	else if (state == ST_MULTILINE)
		return ("multiline");
	else if (state == ST_EOC)
		return ("eoc");
	else
		return (human_state_suite(state));
}

static void	print_state(t_head *head)
{
	t_states	*ptr;

	ptr = GET_NODE(head, t_states, head);
	ft_putstr_fd(human_state(ptr->state), g_debug[1]);
	ft_putchar_fd(' ', g_debug[1]);
}

void		debug_states(t_states *states)
{
	ft_putstr_fd("states: ", g_debug[1]);
	if (states == NULL)
	{
		ft_putendl_fd("Null", g_debug[1]);
		return ;
	}
	list_iter(&(states->head), &print_state);
}

void		debug_flags(int flags)
{
	ft_fdprintf(g_debug[1], " flags: %s\n", human_state(flags));
}
