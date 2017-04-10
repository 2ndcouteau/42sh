/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 19:53:28 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/26 17:12:51 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/get_next_line.h"
#include <stdio.h>

static int		mknl(char *buf, char *ptr_nl, char **line)
{
	char	*tmp;

	tmp = NULL;
	if (!(tmp = *line))
		*line = (ptr_nl != buf) ? ft_strndup(buf, ptr_nl - buf) :
		ft_strnew(0);
	else if (ptr_nl != buf)
	{
		*line = ft_strnjoin(*line, buf, ptr_nl - buf);
		free(tmp);
		tmp = NULL;
	}
	ft_memmove(buf, ptr_nl + 1, ft_strlen(ptr_nl));
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static char	buf[BUFF_SIZE + 1] = {0};
	char		*tmp[2];
	int			ret;

	if ((fd < 0 || BUFF_SIZE < 1 || !line) || (!(*line = NULL) && 0))
		return (-1);
	ft_bzero(tmp, sizeof(char *) * 2);
	ret = BUFF_SIZE;
	while (ret)
	{
		if (buf[0] == 0 && (ret = read(fd, buf, BUFF_SIZE)) < 0)
			return (-1);
		buf[ret] = '\0';
		if ((tmp[1] = ft_strchr(buf, '\n')) && mknl(buf, tmp[1], line))
			return (buf[0] + ret) ? 1 : 0;
		else if ((tmp[0] = *line) || 1)
		{
			*line = (tmp[0]) ? ft_strjoin(*line, buf) : ft_strdup(buf);
			ft_bzero(buf, ft_strlen(buf));
			ft_strdel(&tmp[0]);
			if (ret < BUFF_SIZE)
				return (ret || (*line && **line)) ? 1 : 0;
		}
	}
	return ((*line) ? 1 : 0);
}
