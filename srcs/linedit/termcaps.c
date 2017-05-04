/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 16:29:13 by amoreilh          #+#    #+#             */
/*   Updated: 2017/04/13 19:06:23 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_getcurscoords(t_input *input, t_shell *sh)
{
	int i;
	int j;
	int x;

	i = 1;
	j = 0;
	ft_bzero(input->cursbuff, 10);
	write(0, "\033[6n", 4);
	if (read(0, input->cursbuff, 12) == -1)
		ft_exit(sh, sh->bg_jobs->process);
	x = 0;
	while (++i < 10)
	{
		if ((int)(input->cursbuff[i] - '0') < 10)
			x = x * 10 + (int)(input->cursbuff[i] - '0');
		else if (j < 2)
		{
			j == 0 ? input->cursy = x : 1;
			j == 1 ? input->cursx = x : 1;
			j++;
			x = 0;
		}
	}
}

void	ft_cursgoto(int x, int y, int fd)
{
	ft_fdprintf(fd, "%c[%d;%df", 0x1B, y, x);
}

void	reset_pgrp_ttou(int i)
{
	tcsetpgrp(0, getpid());
	if (g_debug[0])
		ft_fdprintf(g_debug[1], "reset pgrp ttou %d\n", getpid());
	signal(i, reset_pgrp_ttou);
}

int		term_setterm(t_shell *sh)
{
	char			*name_term;
	struct termios	new;

	if ((name_term = ft_getenv(sh->options->env, "TERM")) == NULL
	|| (tgetent(NULL, name_term) <= 0))
	{
		ft_fdprintf(2, "\033[31mValid TERM var needed\033[0m\n\n");
		sh->parser->orig = NULL;
		destroy_shell(&sh);
		exit(EXIT_FAILURE);
	}
	creat_new_term_struct(&new, &sh->options->term);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	if (tcgetpgrp(0) != getpid())
		tcsetpgrp(0, getpid());
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	if ((tcsetattr(STDIN_FILENO, TCSADRAIN, &new)))
	{
		ft_putendl_fd("\033[31mtcsetattr error\n\033[0m", 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGTTOU, reset_pgrp_ttou);
	return (SUCCESS);
}

int		term_resetterm(t_shell *sh)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &(sh->options->term)))
	{
		ft_putstr_fd("\033[31mreconf term error!\033[0m\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (g_debug[0])
		ft_fdprintf(g_debug[1], "\033[91mtcsetattr orig termios ok\033[0m\n");
	return (SUCCESS);
}
