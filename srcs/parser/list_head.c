/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_head.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:56:55 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/22 15:55:13 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t	list_len(t_head *head)
{
	size_t	len;
	t_head	*ptr;

	len = 0;
	ptr = head;
	while (ptr != NULL)
	{
		len++;
		ptr = ptr->next;
	}
	return (len);
}

void	list_append(t_head *head, t_head *new)
{
	t_head	*ptr;

	ptr = head;
	if (new == NULL)
		return ;
	if (ptr != NULL)
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
		new->prev = ptr;
	}
}

t_head	*list_last(t_head *head)
{
	t_head	*ptr;

	if (head == NULL)
		return (NULL);
	ptr = head;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

t_head	*list_pop_last(t_head *head)
{
	t_head	*last;

	if ((last = list_last(head)) == NULL)
		return (NULL);
	if (last->prev != NULL)
		last->prev->next = NULL;
	last->prev = NULL;
	return (last);
}

t_head	*list_pop_first(t_head **head)
{
	t_head	*ptr;

	if ((*head) == NULL)
		return (NULL);
	ptr = (*head);
	(*head) = (*head)->next;
	ptr->next = NULL;
	if ((*head) != NULL)
		(*head)->prev = NULL;
	return (ptr);
}
