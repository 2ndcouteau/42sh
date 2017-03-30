/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 12:28:34 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/22 16:14:12 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_states	*new_state(int state)
{
	t_states	*st;

	st = (t_states*)ft_memalloc(sizeof(t_states));
	st->state = state;
	return (st);
}

void		push_state(t_states **stack, int state)
{
	t_states	*st;

	st = new_state(state);
	if ((*stack) == NULL)
		(*stack) = st;
	else
	{
		list_append(&(st->head), &((*stack)->head));
		(*stack) = st;
	}
}

void		pop_state(t_states **stack)
{
	t_head	*poped;
	t_head	*ptr;

	ptr = &((*stack)->head);
	poped = list_pop_first(&ptr);
	(*stack) = GET_NODE(ptr, t_states, head);
	free(GET_NODE(poped, t_states, head));
}

void		repl_state(t_states **stack, int state)
{
	pop_state(stack);
	push_state(stack, state);
}
