/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 18:00:29 by nboulaye          #+#    #+#             */
/*   Updated: 2017/02/24 15:30:21 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*ft_eval(t_shell *shell, char *code)
{
	int		fds[2];
	int		saved_out;
	char	buff[256];
	char	*out;
	int		i;
	pid_t	pid;
	int		*status;

	status = NULL;
	out = NULL;
	shell->options->bins =
		createbin_hashtab(ft_getenv(shell->options->env, "PATH"));
	if (shell->parser == NULL)
		if (!(shell->parser = new_parser(shell->options)))
			return (NULL);
	shell->parser->orig = ft_strdup(code);
	parse(shell);
	if (!IS_ML(shell->parser))
	{
		if (STATE(shell->parser) != ST_ERR)
		{
			saved_out = dup(STDOUT_FILENO);
			if (pipe(fds))
			{
				ft_fdprintf(2, "pipe error");
				return (NULL);
			}

			if (!(pid = fork()))
			{
				dup2(fds[1], STDOUT_FILENO);
				close(fds[0]);
				shell->script = 1;
				ft_execjobs(shell
					, shell->parser->jobs, shell->parser->opts->env, 0);
				ft_printf("\nhi!\n");
				exit(shell->status);
			}
			else if (pid == -1)
			{
				ft_fdprintf(2, "fork error");
				exit(1);
			}
			else
			{
				if (waitpid(pid, status, 0) == -1)
				{
					ft_fdprintf(2, "wait error");
					exit(1);
				}
			}
			while ((i = read(fds[0], buff, 255)) == 255)
			{
				buff[i] = 0;
				if (out == NULL)
					out = ft_strdup(buff);
				else
					out = ft_strjoinfree(out, ft_strdup(buff));
			}
			if (i > 0)
			{

				buff[i] = 0;
				if (out == NULL)
					out = ft_strdup(buff);
				else
					out = ft_strjoinfree(out, ft_strdup(buff));
			}
			close(fds[1]);
			close(fds[0]);
			dup2(saved_out, STDOUT_FILENO);
			close(saved_out);
			if (i == -1)
				ft_fdprintf(2, "read error\n");
		}
		else
			ft_fdprintf(2, "an error occured.");
		destroy_parser(&(shell->parser));
	}
	else
	{
		ft_fdprintf(2, "code not well formated.");
		return (out);
	}
	return (out);
}

void		test_eval(t_shell *shell, int ac, char **av, char **env)
{
	char	*code;
	char	*ret;

	(void)env;
	code = (ac > 1) ? av[1] : "setenv ok gg;env | grep gg";
	ret = ft_eval(shell, code);
	ft_printf("eval(\"%s\"): returns: %s", code, ret);
	destroy_parser(&(shell->parser));
}
