/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:18:48 by amoreilh          #+#    #+#             */
/*   Updated: 2017/04/13 19:09:39 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_getbranch(void)
{
	int		fd;
	char	*line;
	char	*branche;
	char	*ret;

	fd = 0;
	line = NULL;
	if (!(fd = open("./.git/HEAD", O_RDONLY)))
		return (NULL);
	get_next_line(fd, &line);
	if (fd)
		close(fd);
	if (line && (branche = ft_strrchr(line, '/')))
	{
		ret = ft_strdup(branche + 1);
		free(line);
		return (ret);
	}
	else if (line)
		free(line);
	return (NULL);
}

void	ft_printbranch(void)
{
	char *branch;

	branch = NULL;
	branch = ft_getbranch();
	if (branch)
		ft_fdprintf(2, " \033[38;5;208m(\033[38;5;240m%s\033[38;5;208m)"
			, branch);
	free(branch);
}

void	ft_disppromptpath(char *ho, char *u, char *buf)
{
	int len;

	if (ho && buf[0] && (ft_strncmp(ho, buf, ft_strlen(ho)) == 0))
	{
		len = ft_strlen((ft_strrchr(buf, '/')));
		ft_putstr_fd("\033[38;5;208m~ \033[38;5;240m", 2);
		if (ft_strncmp(&buf[ft_strlen(ho) + 1], ft_strrchr(buf, '/') + 1, len))
			write(2, &buf[ft_strlen(ho) + 1],
				(ft_strlen(&buf[ft_strlen(ho)]) - len));
		ft_putstr_fd("\033[38;5;208m", 2);
		if (!u || (ft_strncmp(ft_strrchr(buf, '/') + 1, u, ft_strlen(u)) != 0))
			ft_putstr_fd(ft_strrchr(buf, '/') + 1, 2);
	}
	else if (buf[0])
	{
		len = ft_strlen((ft_strrchr(buf, '/')));
		if (ft_strncmp(buf, ft_strrchr(buf, '/') + 1, len) != 0)
			write(2, buf, (ft_strlen(buf) - len + 1));
		ft_putstr_fd("\033[38;5;208m", 2);
		ft_putstr_fd(ft_strrchr(buf, '/') + 1, 2);
	}
	else
		ft_putstr_fd("undefined", 2);
	ft_printbranch();
	ft_putendl_fd("\033[0m", 2);
}

void	ft_prompt(t_input *input, t_shell *sh)
{
	char *us;
	char *ho;
	char buf[PROMPTBUF];

	us = ft_getenv(sh->parser->opts->env, "USER");
	if (input->prompt)
	{
		ft_bzero(buf, PROMPTBUF);
		getcwd(buf, PROMPTBUF);
		ho = ft_getenv(sh->parser->opts->env, "HOME");
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("\033[38;5;208m▶  \033[38;5;240m", 2);
		ft_disppromptpath(ho, us, buf);
	}
	input->prompt2 = us ? ft_strjoin(us, "@42sh > ") : ft_strdup("42sh > ");
	input->prompt2len = ft_strlen(input->prompt2);
}

void	ft_freecomplist(t_autocomp *autoc)
{
	t_compnode *cur;

	cur = autoc->first;
	while (cur)
	{
		free(cur->word);
		free(cur);
		cur = (cur->head.next) ?
		GET_NODE(cur->head.next, t_compnode, head) : NULL;
	}
}
