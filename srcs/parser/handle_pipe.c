/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 21:11:16 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/18 14:55:02 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	handle_pipe_suite(t_parser *p)
{
	t_processes *proc;

	if (get_last_cmd(get_last_process(
		get_last_job(p->jobs)->process)->cmds)->argv == NULL)
	{
		ft_fdprintf(2, "\x1b[31mleft pipe missing\x1b[0m\n");
		push_state(&(p->states), ST_ERR);
		return ;
	}
	merge_part(p);
	proc = get_new_process(&(get_last_job(p->jobs)->process));
	proc->cmds = new_cmds();
	p->last_cmd = proc->cmds;
	p->first_word = 1;
}

void		handle_pipe(t_parser *p)
{
	t_cmds		*cmd;

	p->idx++;
	if (*CURRENT(p) == '|')
	{
		if ((cmd = get_last_cmd(get_last_process(
			get_last_job(p->jobs)->process)->cmds)) != NULL)
			get_last_job(p->jobs)->flags = ST_OR;
		if (get_last_cmd(
			get_last_process(
			get_last_job(p->jobs)->process)->cmds)->argv == NULL)
		{
			ft_putendl_fd("parse error", 2);
			push_state(&(p->states), ST_ERR);
		}
		else
		{
			merge_part(p);
			handle_eoc(p);
			repl_state(&(p->states), ST_EOC);
		}
	}
	else
		handle_pipe_suite(p);
}
