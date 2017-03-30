/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_jobs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/02/18 19:53:17 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	chk_bg(t_jobs **bg_jobs)
{
	t_jobs *bg_jobs_parser;

	if (g_debug[0])
		ft_fdprintf(g_debug[1], "\033[31mCHK BG\n\033[0m");
	if (!bg_jobs)
		return ;
	if ((bg_jobs_parser = *bg_jobs))
		while (bg_jobs_parser)
		{
			if (g_debug[0])
			{
				ft_fdprintf(g_debug[1], "\033[31m pgid:%d, status:%d\033[0m -->"
				, bg_jobs_parser->pgid, bg_jobs_parser->status);
				printarg((bg_jobs_parser)->process, NULL, g_debug[1]);
			}
			wait_bg(bg_jobs, bg_jobs_parser);
			bg_jobs_parser = (bg_jobs_parser && bg_jobs_parser->process
				&& bg_jobs_parser->pgid && bg_jobs_parser->head.next)
			? GET_NODE((bg_jobs_parser->head.next), t_jobs, head) : NULL;
		}
}

void	ft_execjobs(t_shell *sh, t_jobs *j, t_dict *env, int preflag)
{
	void	*j_sav;

	while ((j_sav = j))
	{
		j->process->env = env;
		if (preflag == ST_OR && sh->status == 0)
			;
		else if (!(preflag == ST_AND && sh->status != 0)
		&& j->process && j->process->cmds && j->process->cmds->argv)
			ft_execprocess(&j, j->process, sh, j->process->env);
		preflag = (j) ? j->flags : 0;
		if (j == j_sav)
		{
			j = (j && j->head.next) ?
			GET_NODE((j->head.next), t_jobs, head) : NULL;
			chk_bg(&sh->bg_jobs);
		}
		else if (j && !j->head.prev)
			sh->parser->jobs = j;
	}
}
