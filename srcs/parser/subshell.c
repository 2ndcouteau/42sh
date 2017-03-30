/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 14:51:49 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/24 15:12:57 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_subshell	*new_subshell(/*char *code,*/ int idx)
{
	t_subshell	*sub;

	if ((sub = (t_subshell*)ft_memalloc(sizeof(t_subshell))) == NULL)
		return (NULL);
	//sub->code = code;
	sub->idx = idx;
	return (sub);
}
