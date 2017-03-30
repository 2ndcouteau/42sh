/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 03:10:04 by nboulaye          #+#    #+#             */
/*   Updated: 2016/10/25 06:20:40 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 0xFF
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct			s_bufline
{
	int					fd;
	char				*nxtline;
	struct s_bufline	*next;
}						t_bufline;

int						get_next_line(int const fd, char **line);

#endif
