/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_proc2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 22:55:14 by nboulaye          #+#    #+#             */
/*   Updated: 2017/04/12 17:34:02 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char		*get_code(char *str, int *idxs)
{
	return (ft_strsub(str, idxs[0], idxs[1] - idxs[0]));
}

char		*get_eval(t_shell *shell, char *code)
{
	char *ret;
	char *ptr;

	if ((ret = ft_eval(shell, code)) == NULL)
		return (NULL);
	ptr = ret;
	ret = ft_strtrim(ptr);
	ft_strdel(&ptr);
	return (ret);
}
