/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:54:32 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/28 22:44:49 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	update_part(t_parser *p, char *part)
{
	if (part == NULL)
		return ;
	if (p->part == NULL)
	{
		p->part = ft_strdup(part);
		ft_memdel((void **)&part);
	}
	else
		p->part = ft_strjoinfree(p->part, part);
}

void	merge_part(t_parser *p)
{
	t_cmds	*cmd;

	if (p->merge)
	{
		if (p->part == NULL || (ft_strcmp(p->part, "") == 0))
			return ;
		cmd =
		get_last_cmd(get_last_process(get_last_job(p->jobs)->process)->cmds);
		ft_stabpush(&(cmd->argv), p->part);
		ft_strdel(&(p->part));
	}
}

void	make_error(t_parser *p, char *mess)
{
	p->errmess = mess;
	add_state(&(p->states), ST_ERR);
}
