/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_head2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 15:54:12 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/22 15:54:21 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	list_iter(t_head *head, void (*fct)(t_head*))
{
	t_head	*ptr;
	t_head	*next;

	if (head == NULL)
		return ;
	ptr = head;
	while (ptr != NULL)
	{
		next = ptr->next;
		fct(ptr);
		ptr = next;
	}
}

void	list_pop_one(t_head *head)
{
	t_head *prev;
	t_head *next;

	prev = head->prev;
	next = head->next;
	if (prev != NULL)
		prev->next = next;
	if (next != NULL)
		next->prev = prev;
	head->next = NULL;
	head->prev = NULL;
}

void	list_replace_one(t_head *old, t_head *new)
{
	new->prev = old->prev;
	new->next = old->next;
	old->next = NULL;
	old->prev = NULL;
}

t_head	*list_get_first(t_head *head, void *args, char (*test)(t_head*, void*))
{
	t_head	*ptr;

	ptr = head;
	while (ptr != NULL)
	{
		if (test(ptr, args) != 0)
			break ;
		ptr = ptr->next;
	}
	return (ptr);
}
