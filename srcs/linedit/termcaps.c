/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 16:29:13 by amoreilh          #+#    #+#             */
/*   Updated: 2017/03/26 19:28:51 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_getcurscoords(t_input *input)
{
	int i;
	int j;
	int x;

	i = 1;
	j = 0;
	ft_bzero(input->cursbuff, 10);  // Why bzero on 10 char instead of cursbuff size is 12 ???
	write(0, "\033[6n", 4);
	if (read(0, input->cursbuff, 12) == -1)		// Here you read 12 ! Need check read() return;
		exit (EXIT_FAILURE); // NEED TO CREATE AN EXIT FUNCTION;
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

int		term_setterm(t_shell *sh)
{
	char			*name_term;
	struct termios	new;

	if ((name_term = ft_getenv(sh->options->env, "TERM")) == NULL
	|| (tgetent(NULL, name_term) <= 0))
	{
		ft_fdprintf(2, "\033[31mValid TERM var needed\033[0m\n\n");
		sh->parser->orig = NULL;	//ft_strnew(0);// je comprends pas pk il faut faire ca avant de destroy ici!
		destroy_shell(&sh);
		exit(EXIT_FAILURE);
	}
	creat_new_term_struct(&new, &sh->options->term);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	if (tcgetpgrp(0) != getpid())
		tcsetpgrp(0, getpid());
	// signal(SIGTTIN, test);
	// signal(SIGTTOU, test);
	if ((tcsetattr(STDIN_FILENO, TCSADRAIN, &new)))				// Why OPTION is different from term_reseterm()
	{
		ft_putendl_fd("\033[31mtcsetattr error\n\033[0m", 2);
		exit(EXIT_FAILURE);
	}
	// signal(SIGTTIN, test);
	// signal(SIGTTOU, test);
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
