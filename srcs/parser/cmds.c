/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 15:44:36 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/20 16:51:50 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_cmds		*new_cmds(void)
{
	t_cmds	*cmds;

	cmds = (t_cmds*)ft_memalloc(sizeof(t_cmds));
	return (cmds);
}

static void	del_cmd(t_head *head)
{
	t_cmds *ptr;

	ptr = GET_NODE(head, t_cmds, head);
	if (ptr->argv != NULL)
		ft_stabdel(&(ptr->argv));
	ft_memdel((void **)&ptr);
	ptr = NULL;
}

void		destroy_cmds(t_cmds **cmds)
{
	if ((*cmds) == NULL)
		return ;
	list_iter(&((*cmds)->head), &del_cmd);
	(*cmds) = NULL;
}
