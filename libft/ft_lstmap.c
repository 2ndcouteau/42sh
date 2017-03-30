/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 19:50:29 by nboulaye          #+#    #+#             */
/*   Updated: 2015/12/04 23:48:46 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ret;
	t_list	*tmp;

	if (!(tmp = f(lst)))
		return (NULL);
	ret = tmp;
	while ((lst = lst->next))
	{
		tmp->next = f(lst);
		tmp = tmp->next;
	}
	return (ret);
}
