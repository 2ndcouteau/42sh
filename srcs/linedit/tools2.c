/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 16:29:13 by amoreilh          #+#    #+#             */
/*   Updated: 2017/03/24 19:28:57 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	creat_new_term_struct(struct termios *new, struct termios *old)
{
	int i;

	new->c_iflag = old->c_iflag;
	new->c_oflag = old->c_oflag;
	new->c_cflag = old->c_cflag;
	new->c_lflag = old->c_lflag;
	i = -1;
	while (++i < 20)
		new->c_cc[i] = old->c_cc[i];
	new->c_lflag &= ~(ECHO | ICANON | ISIG);
	new->c_cc[VMIN] = 1;
	new->c_cc[VTIME] = 0;
}

int		ft_isfirstword(t_input *input, char *line)
{
	int pos;

	pos = input->prompt2len;
	while (!ft_isspace(line[pos]) && line[pos] && pos < input->bufposmax
	&& (pos < (input->buffsize - 1)))
		pos++;
	if (pos >= input->bufpos)
		return (1);
	else
		return (0);
}

char	*linedit_reallocbuff(t_input *input)
{
	char *save;

	save = I->line;
	if (!(I->line = (char *)ft_memalloc(sizeof(char) * (I->buffsize * 2))))
		return (NULL);
	I->buffsize *= 2;
	ft_strncpy(I->line, save, I->buffsize);
	free(save);
	return (I->line);
}

int		term_isfolder(char *path)
{
	struct stat buf;

	stat(path, &buf);
	if ((S_ISDIR(buf.st_mode)))
		return (SUCCESS);
	return (ERROR);
}
