/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 20:53:47 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/10 04:24:12 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	parse_n_exec_script(t_shell *sh)
{
	parse(sh);
	if ((STATE(sh->parser) != ST_MULTILINE)
	&& (STATE(sh->parser) != ST_ONELINE)
	&& STATE(sh->parser) != ST_HEREDOC)
	{
		if (STATE(sh->parser) != ST_ERR)
			ft_execjobs(sh, sh->parser->jobs
			, sh->parser->opts->env, 0);
		destroy_parser(&(sh->parser));
	}
	else
	{
		if (sh->parser->orig[ft_strlen(sh->parser->orig)] != '\\')
			sh->parser->orig =
			ft_strjoinfree(sh->parser->orig, ft_strdup("\n"));
		if (STATE(sh->parser) != ST_ONELINE)
			pop_state(&(sh->parser->states));
	}
}

int			script_loop(t_shell *sh)
{
	char	*line;

	sh->options->bins =
		createbin_hashtab(ft_getenv(sh->options->env, "PATH"));
	while (get_next_line(sh->options->fd, &line) != 0)
	{
		if (sh->parser == NULL)
			if (!(sh->parser = new_parser(sh->options)))
				return (1);
		if (sh->parser->orig == NULL)
		{
			sh->parser->orig = ft_strdup(line);
			free(line);
		}
		else
			sh->parser->orig = ft_strjoinfree(sh->parser->orig, line);
		line = NULL;
		parse_n_exec_script(sh);
	}
	return (0);
}
