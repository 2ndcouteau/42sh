/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 12:55:36 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/20 18:59:00 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell	*new_shell(t_options *opts)
{
	t_shell	*shell;

	shell = (t_shell*)ft_memalloc(sizeof(t_shell));
	shell->options = opts;
	shell->parser = NULL;
	if ((shell->history = new_history_list(opts->env)) == NULL)
		destroy_shell(&shell);
	return (shell);
}

void	destroy_shell(t_shell **shell)
{
	if (shell && *shell)
	{
		if ((*shell)->options)
			destroy_options(&((*shell)->options));
		if ((*shell)->history)
			destroy_history((*shell)->history);
		if ((*shell)->parser)
			destroy_parser(&((*shell)->parser));
	}
	ft_memdel((void **)&(*shell));
}
