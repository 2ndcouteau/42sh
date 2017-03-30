/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 18:14:49 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/20 21:27:40 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	handle_heredoc(t_parser *p)
{
	t_redir	*red;
	int		lena;
	int		lenh;

	if ((red = get_current_redir(p)) != NULL &&
		red->heredoc != NULL && red->arg != NULL)
	{
		lena = ft_strlen(red->arg);
		lenh = ft_strlen(red->heredoc);
		if (lenh >= lena &&
			ft_strcmp(&(red->heredoc[lenh - lena]), red->arg) == 0 &&
			((lenh == lena) || red->heredoc[lenh - lena - 1] == 10))
		{
			pop_state(&(p->states));
			red->heredoc_done = 1;
			push_state(&(p->states), ST_PASS);
			if (lenh > lena)
				red->heredoc[lenh - lena - 1] = 0;
			else
				red->heredoc[0] = 0;
		}
	}
}
