/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 16:13:20 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/22 16:13:29 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		add_state(t_states **stack, int state)
{
	push_state(stack, state);
	if (state != ST_PASS)
		push_state(stack, ST_PASS);
}

static void	del_state(t_head *head)
{
	t_states	*state;

	state = GET_NODE(head, t_states, head);
	ft_memdel((void **)&state);
}

void		destroy_states(t_states **states)
{
	if ((*states) == NULL)
		return ;
	list_iter(&((*states)->head), &del_state);
}
