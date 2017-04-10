/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history_print.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 19:14:14 by qrosa             #+#    #+#             */
/*   Updated: 2017/04/07 21:17:05 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "history.h"

static int	print_all_history(t_history *h, int i)
{
	while (h)
	{
		ft_printf("% 6d %s%s", ++i, h->value, (h->head.next) ? "\n" : "");
		h = (h->head.next)
			? GET_NODE((h->head.next), t_history, head) : NULL;
	}
	return (SUCCESS);
}

static void	print_n_end(t_history *h, int cpt)
{
	t_head	*ptr;
	int		len;

	len = 0;
	ptr = &(h->head);
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		len++;
	}
	while (cpt > 1 && len > 0)
	{
		ptr = ptr->prev;
		--cpt;
		--len;
	}
	h = GET_NODE(ptr, t_history, head);
	while (h)
	{
		ft_printf("% 6d %s%s", len++, h->value, (h->head.next) ? "\n" : "");
		h = (h->head.next)
					? GET_NODE((h->head.next), t_history, head) : NULL;
	}
}

static int	print_n_history(char **tab_arg, t_history *h)
{
	int		cpt;

	cpt = !ft_isnumber(tab_arg[1]) ? ft_atoi(tab_arg[1]) : -1;
	if (cpt < 0)
	{
		ft_fdprintf(2, "history: %s numeric argument required\n", tab_arg[1]);
		return (ERROR);
	}
	else if (cpt > 0)
		print_n_end(h, cpt);
	return (SUCCESS);
}

int			builtin_history_print(char **tab_arg, t_history *h, int i)
{
	if (tab_arg[1] == NULL)
		return (print_all_history(h, i));
	if (tab_arg[2] == NULL)
		return (print_n_history(tab_arg, h) ? SUCCESS : ERROR);
	ft_fdprintf(2, "42sh: history: too many arguments\n", tab_arg[1]);
	return (ERROR);
}
