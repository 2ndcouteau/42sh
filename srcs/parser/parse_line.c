/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:52:56 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/20 17:53:22 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*forward_escape(char *str, const char *charset)
{
	while (*str != 0 && ft_strchr(charset, *str) == NULL)
		str++;
	return (str);
}

char	*forward_with(char *str, const char *charset)
{
	while (*str != 0 && ft_strchr(charset, *str) != NULL)
		str++;
	return (str);
}
