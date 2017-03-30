/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_head.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 21:06:33 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/19 20:50:17 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HEAD_H
# define LIST_HEAD_H
# define GET_NODE(p, t, m) ((t *)((char *)(p) - (unsigned long)(&((t *)0)->m)))

typedef struct			s_head
{
	struct s_head		*next;
	struct s_head		*prev;
}						t_head;

typedef struct s_shell	t_shell;

void					list_append(t_head *head, t_head *new);
void					list_iter(t_head *head, void (*fct)(t_head*));
size_t					list_len(t_head *head);
t_head					*list_last(t_head *head);
t_head					*list_pop_first(t_head **head);
void					list_pop_one(t_head *head);
void					list_replace_one(t_head *old, t_head *new);
void					list_push(t_head *head, t_head *new);
t_head					*list_get_first (t_head *head,
	void *args, char (*cmp)(t_head*, void*));

#endif
