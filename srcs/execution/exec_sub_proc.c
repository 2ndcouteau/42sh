/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_proc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/04/26 22:44:35 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*str_repl(char *str, char *old, char *new, int len)
{
	char *pre;
	char *post;

	pre = ft_strsub(str, 0, len);
	post = ft_strsub(str,
		len + ft_strlen(old),
		ft_strlen(str) - (len + ft_strlen(old)));
	return (ft_strjoinfree(pre, ft_strjoinfree(ft_strdup(new), post)));
}

static int	replace_instring(t_shell *shell, t_subshell *sub,
	t_processes **proc)
{
	ssize_t	i;
	char	*code;
	char	*newstr;
	char	*output;

	i = itab_len(sub->instring);
	while (--i >= 0)
	{
		if ((code = get_code((*proc)->cmds->argv[sub->idx],
			sub->instring[i])) != NULL)
		{
			if ((output = get_eval(shell, code)) != NULL)
			{
				newstr = str_repl((*proc)->cmds->argv[sub->idx], code, output,
					sub->instring[i][0]);
				ft_strdel(&output);
				ft_strdel(&code);
				ft_strdel(&((*proc)->cmds->argv[sub->idx]));
				(*proc)->cmds->argv[sub->idx] = newstr;
			}
			else
				return (1);
		}
	}
	return (0);
}

static char	**replace_normal(char **argv, char *output, int idx)
{
	char	**splited;
	char	**new_av;
	size_t	len_out;
	size_t	i;

	new_av = NULL;
	if ((splited = ft_strsplit(output, '\n')))
	{
		len_out = ft_stablen(splited);
		new_av = ft_stabnew(ft_stablen(argv) + len_out);
		i = 0;
		while (i < ft_stablen(argv) + len_out)
		{
			if (i < (size_t)idx)
				new_av[i] = ft_strdup(argv[i]);
			else if (i < (size_t)idx + len_out)
				new_av[i] = ft_strdup(splited[i - idx]);
			else if (i - len_out + 1 < ft_stablen(argv))
				new_av[i] = ft_strdup(argv[i - len_out + 1]);
			i++;
		}
		ft_stabdel(&splited);
	}
	return (new_av);
}

static void	replace_subshells_suite(t_shell *shell, t_processes **proc,
	t_subshell *ptr)
{
	char	*output;
	char	**av_ptr;

	if ((output = get_eval(shell, (*proc)->cmds->argv[ptr->idx])) != NULL)
	{
		av_ptr = (*proc)->cmds->argv;
		(*proc)->cmds->argv = replace_normal(av_ptr, output, ptr->idx);
		ft_stabdel(&av_ptr);
		ft_strdel(&output);
	}
}

int			replace_subshells(t_shell *shell, t_processes **proc)
{
	t_subshell	*ptr;
	t_parser	*mem;

	if ((*proc)->subshell && (*proc)->cmds && (*proc)->cmds->argv)
	{
		ptr = GET_NODE(list_last(&((*proc)->subshell->head)), t_subshell, head);
		while (ptr)
		{
			mem = shell->parser;
			shell->parser = NULL;
			if (ptr->instring == NULL)
				replace_subshells_suite(shell, proc, ptr);
			else if (replace_instring(shell, ptr, proc) == 1)
				return (1);
			destroy_parser(&(shell->parser));
			shell->parser = mem;
			if (ptr->head.prev == NULL)
				break ;
			ptr = GET_NODE(ptr->head.prev, t_subshell, head);
		}
	}
	return (0);
}
