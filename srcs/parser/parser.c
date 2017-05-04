/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:33:57 by ljohan            #+#    #+#             */
/*   Updated: 2017/04/13 19:04:28 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_parser	*new_parser(t_options *opts)
{
	t_parser	*p;

	if ((p = (t_parser*)ft_memalloc(sizeof(t_parser))) == NULL)
		return (NULL);
	p->part = NULL;
	if ((p->jobs = new_jobs()) == NULL
	|| (p->jobs->process = new_processes()) == NULL
	|| (p->jobs->process->env = opts->env) == NULL
	|| (p->jobs->process->cmds = new_cmds()) == NULL
	|| (p->states = new_state(ST_INIT)) == NULL
	|| (p->orig = ft_strnew(0)) == NULL)
	{
		destroy_parser(&p);
		return (NULL);
	}
	p->last_cmd = p->jobs->process->cmds;
	p->idx = 0;
	p->errmess = NULL;
	p->opts = opts;
	p->first_word = 1;
	p->aliases_done = 0;
	p->eof = 0;
	p->merge = 1;
	return (p);
}

void		destroy_parser(t_parser **p)
{
	if ((*p) == NULL)
		return ;
	if ((*p)->orig != NULL)
		ft_strdel(&(*p)->orig);
	if ((*p)->errmess != NULL)
		ft_strdel(&((*p)->errmess));
	if ((*p)->part != NULL)
		ft_strdel(&((*p)->part));
	if ((*p)->states != NULL)
		destroy_states(&((*p)->states));
	if ((*p)->jobs != NULL)
		destroy_jobs(&((*p)->jobs));
	ft_memdel((void **)&*p);
	(*p) = NULL;
}

int			reset_parser(t_parser **p)
{
	if ((*p) != NULL)
	{
		if ((*p)->orig != NULL)
			ft_strdel(&((*p)->orig));
		if ((*p)->part != NULL)
			ft_strdel(&((*p)->part));
		if ((*p)->states != NULL)
		{
			destroy_states(&((*p)->states));
			if (((*p)->states = new_state(ST_INIT)) == NULL)
			{
				destroy_parser(p);
				return (1);
			}
		}
		(*p)->idx = 0;
		(*p)->first_word = 1;
		(*p)->eof = 0;
		return (0);
	}
	return (1);
}

void		handle_aliases(t_parser *p, char *key, char *alias)
{
	char	*pre;
	char	*post;
	size_t	lk;

	lk = ft_strlen(key);
	pre = ft_strsub(p->orig, 0, p->idx);
	post = ft_strsub(p->orig, p->idx + lk, ft_strlen(p->orig));
	ft_strdel(&(p->orig));
	p->orig = ft_strjoin3(pre, alias, post);
	ft_memdel((void **)&post);
	ft_memdel((void **)&pre);
}
