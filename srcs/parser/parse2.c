/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 16:11:33 by ljohan            #+#    #+#             */
/*   Updated: 2017/04/12 21:10:37 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	spec_char(char *e, t_parser *p)
{
	if (e[0] == 'n')
		e[0] = '\n';
	else if (e[0] == 't')
		e[0] = '\t';
	else if (e[0] == 'a')
		e[0] = '\a';
	else if (e[0] == 'b')
		e[0] = '\b';
	else if (e[0] == 'E')
		e[0] = '\E';
	else if (e[0] == 'e')
		e[0] = '\e';
	else if (e[0] == 'f')
		e[0] = '\f';
	else if (e[0] == 'r')
		e[0] = '\r';
	else if (e[0] == 'v')
		e[0] = '\v';
	else if (e[0] == '\\')
		e[0] = '\\';
	p->idx++;
}

char		*parse_escape(t_parser *p)
{
	char	e[2];
	t_cmds	*cmd;

	p->idx++;
	e[0] = *CURRENT(p);
	e[1] = 0;
	cmd = get_last_cmd(get_last_process(get_last_job(p->jobs)->process)->cmds);
	if (GET_NODE(p->states->head.next, t_states, head)->state == ST_STR)
	{
		if (cmd != NULL && cmd->argv && ft_stablen(cmd->argv)
		&& ft_strcmp(cmd->argv[0], "echo") == 0)
			spec_char(e, p);
	}
	else if (*CURRENT(p) == 0)
		repl_state(&(p->states), ST_ONELINE);
	else
		p->idx++;
	return (ft_strdup((char*)e));
}

char		*parse_oneline(t_parser *p)
{
	if (IS_BLANK(*CURRENT(p)))
	{
		pop_state(&(p->states));
		return (parse_normal(p));
	}
	p->idx--;
	return (parse_escape(p));
}

char		*parse_bg(t_parser *p)
{
	t_cmds	*cmd;

	if (*CURRENT(p) == '&')
	{
		if ((cmd = get_last_cmd(get_last_process(
			get_last_job(p->jobs)->process)->cmds)) != NULL)
			get_last_job(p->jobs)->flags = ST_AND;
		merge_part(p);
		handle_eoc(p);
		repl_state(&(p->states), ST_EOC);
		return (NULL);
	}
	else
	{
		if ((cmd = get_last_cmd(get_last_process(
			get_last_job(p->jobs)->process)->cmds)) != NULL)
			get_last_job(p->jobs)->flags = ST_BG;
		merge_part(p);
		handle_eoc(p);
		return (NULL);
	}
}
