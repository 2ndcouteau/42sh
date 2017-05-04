/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 20:53:47 by ljohan            #+#    #+#             */
/*   Updated: 2017/04/27 19:21:06 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		catch_keyboard_sig(char var)
{
	if (var == 1)
	{
		signal(SIGWINCH, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
	}
	else if (var == 0)
	{
		signal(SIGWINCH, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
	}
}

void		parse_n_exec_suite(t_shell *sh)
{
	catch_keyboard_sig(0);
	if (sh->parser->orig[0] != ' ')
		add_history(sh->parser->orig, &(sh->history));
	if (STATE(sh->parser) == ST_EOF)
		ft_execjobs(sh, sh->parser->jobs, sh->parser->opts->env, 0);
	else if (STATE(sh->parser) != ST_ERR)
		;
	else if (g_debug[0])
		ft_fdprintf(g_debug[1], "Unhandled parser state '%s'\n",
			human_state(STATE(sh->parser)));
	destroy_parser(&(sh->parser));
}

void		parse_n_exec(t_shell *sh)
{
	if (sh->parser == NULL)
		if (!(sh->parser = new_parser(sh->options)))
			return ;
	if (STATE(sh->parser) == ST_MULTILINE)
		pop_state(&(sh->parser->states));
	parse(sh, 0);
	debug_dict(sh->options->env);
	if ((STATE(sh->parser) != ST_MULTILINE) && (STATE(sh->parser)
		!= ST_ONELINE) && (STATE(sh->parser) != ST_HEREDOC)
		&& sh->parser->orig != NULL)
		parse_n_exec_suite(sh);
	else if (sh->parser->orig != NULL)
	{
		if (sh->parser->orig[ft_strlen(sh->parser->orig)] != '\\')
			sh->parser->orig =
				ft_strjoinfree(sh->parser->orig, ft_strdup("\n"));
	}
}

int			main_loop(t_shell *sh, char stop)
{
	pid_t	shell_pgid;
	char	*ptr;

	while (tcgetpgrp(STDIN_FILENO) != (shell_pgid = getpgrp()))
		kill(-shell_pgid, SIGTTIN);
	ptr = NULL;
	sh->options->bins = createbin_hashtab(ft_getenv(sh->options->env, "PATH"));
	while (!stop || sh->bg_jobs)
	{
		catch_keyboard_sig(1);
		if (!(stop = event_loop(sh, &ptr)))
			parse_n_exec(sh);
		else if (stop == 2)
		{
			destroy_parser(&(sh->parser));
			stop = 0;
		}
		else
			ft_exit(sh, NULL);
	}
	return (0);
}

int			main(int ac, char **av, char **env)
{
	t_shell	*sh;

	g_debug[0] = 0;
	if (ac == 2 && ft_strnequ(av[1], "debug", 5) && av[1][5] == '=')
		debug(1, &av[1][6]);
	sh = new_shell(new_options(ac, av, env));
	if (sh->options->fd == 0 && isatty(sh->options->fd))
	{
		sh->script = 0;
		main_loop(sh, 0);
	}
	else
	{
		sh->script = 1;
		script_loop(sh);
	}
	destroy_shell(&sh);
	if (g_debug[0])
		debug(0, NULL);
	return (0);
}
