/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 14:25:34 by nboulaye          #+#    #+#             */
/*   Updated: 2016/01/06 23:13:56 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*newlst;

	if (!(newlst = (t_list *)ft_memalloc(sizeof(t_list))))
		return (NULL);
	newlst->next = NULL;
	newlst->content = NULL;
	newlst->content_size = 0;
	if (content && content_size)
	{
		newlst->content = ft_memalloc(content_size);
		ft_memcpy(newlst->content, content, content_size);
		newlst->content_size = content_size;
	}
	return (newlst);
}
