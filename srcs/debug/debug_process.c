/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:07:16 by qrosa             #+#    #+#             */
/*   Updated: 2017/04/12 17:11:26 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	debug_subshell_instring(int **instring)
{
	size_t	i;

	if (!instring)
		return ;
	i = 0;
	while (instring[i] != NULL)
	{
		ft_fdprintf(g_debug[1], " [%d,%d]", instring[i][0], instring[i][1]);
		i++;
	}
}

static void	in_debug_cmds(char **str)
{
	int			j;

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
	int			i;
	t_cmds		*ptr;
	char		**str;

	if (c == NULL)
		ft_putstr_fd("cmds: NULL", g_debug[1]);
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

void		debug_subshell(t_subshell *sub)
{
	ft_fdprintf(g_debug[1], "subshell: ");
	if (sub == NULL)
		ft_fdprintf(g_debug[1], "null\n");
	else
	{
		ft_fdprintf(g_debug[1], "idxs:");
		while (sub)
		{
			ft_fdprintf(g_debug[1], " (%d: ", sub->idx);
			if (sub->instring != NULL)
				debug_subshell_instring(sub->instring);
			ft_putstr_fd(")", g_debug[1]);
			if (sub->head.next == NULL)
			{
				ft_putstr_fd("\n", g_debug[1]);
				break ;
			}
			sub = GET_NODE(sub->head.next, t_subshell, head);
		}
	}
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
