/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 15:58:17 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/24 15:13:52 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	in_debug_cmds(char **str)
{
	int	j;

	j = 0;
	while (str[j] != NULL)
	{
		ft_putstr_fd(str[j], g_debug[1]);
		if (str[j + 1] != NULL)
			ft_putstr_fd(", ", g_debug[1]);
		j++;
	}
	ft_putchar_fd('\n', g_debug[1]);
}

void		debug_cmds(t_cmds *c)
{
	int		i;
	t_cmds	*ptr;
	char	**str;

	if (c == NULL)
		ft_putstr_fd("cmds: Null", g_debug[1]);
	else
	{
		i = 0;
		ptr = c;
		while (ptr != NULL)
		{
			ft_fdprintf(g_debug[1], "  c %d: ", i++);
			str = ptr->argv;
			if (str != NULL)
				in_debug_cmds(str);
			else
				ft_putendl_fd("null", g_debug[1]);
			if (ptr->head.next == NULL)
				break ;
			ptr = GET_NODE(ptr->head.next, t_cmds, head);
		}
	}
}

void	debug_subshell(t_subshell *sub)
{
	ft_fdprintf(g_debug[1], "subshell: ");
	if (sub == NULL)
		ft_fdprintf(g_debug[1], "null\n");
	else
		ft_fdprintf(g_debug[1], "idx: %d\n",sub->idx);
		// ft_fdprintf(g_debug[1], "\n\tcode: %s\n\tidx: %d\n", sub->code, sub->idx);
}

void		debug_process(t_processes *p)
{
	int			i;
	t_processes	*ptr;

	if (p == NULL)
		ft_putstr_fd("Null", g_debug[1]);
	else
	{
		i = 0;
		ptr = p;
		while (ptr != NULL)
		{
			ft_putstr_fd(" p ", g_debug[1]);
			ft_putnbr_fd(i++, g_debug[1]);
			ft_putchar_fd('\n', g_debug[1]);
			debug_cmds(ptr->cmds);
			debug_redir(ptr->redir);
			debug_subshell(ptr->subshell);
			if (ptr->head.next == NULL)
				break ;
			ptr = GET_NODE(ptr->head.next, t_processes, head);
		}
	}
}

void		debug_jobs(t_jobs *j)
{
	int		i;
	t_jobs	*ptr;

	ft_putendl_fd("\n=== JOBS DEBUG ===", g_debug[1]);
	if (j == NULL)
		ft_putstr_fd("Null", g_debug[1]);
	else
	{
		i = 0;
		ptr = j;
		while (ptr != NULL)
		{
			ft_putstr_fd("j ", g_debug[1]);
			ft_putnbr_fd(i++, g_debug[1]);
			ft_putchar_fd('\n', g_debug[1]);
			debug_process(ptr->process);
			debug_flags(ptr->flags);
			ptr = (ptr->head.next) ? \
				GET_NODE(ptr->head.next, t_jobs, head) : NULL;
		}
	}
	ft_putendl_fd("\n=== END ===", g_debug[1]);
}

void		debug_parser(t_parser *parser)
{
	int i;

	i = -1;
	ft_fdprintf(g_debug[1], "\norig: %s\n", parser->orig != NULL ? \
		parser->orig : "Null");
	ft_putstr_fd("      ", g_debug[1]);
	while (++i < parser->idx)
		ft_putchar_fd(' ', g_debug[1]);
	ft_putendl_fd("^", g_debug[1]);
	ft_fdprintf(g_debug[1], "part: %s\n", parser->part != NULL ? \
		parser->part : "Null");
	debug_states(parser->states);
	ft_putchar_fd('\n', g_debug[1]);
	debug_jobs(parser->jobs);
}
