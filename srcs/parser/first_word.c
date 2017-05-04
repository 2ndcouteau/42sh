/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:01:16 by ljohan            #+#    #+#             */
/*   Updated: 2017/04/27 23:26:02 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*get_str_hist(t_shell *sh, int idx, char *new_value, char i)
{
	t_history	*hist;

	hist = (!i) ? sh->history :
	GET_NODE(list_last(&sh->history->head), t_history, head);
	if (idx > 0)
		while (--idx && hist
		&& ((!i && hist->head.next) || (i && hist->head.prev)))
			hist = (!i) ? GET_NODE(((hist)->head.next), t_history, head) :
				GET_NODE(((hist)->head.prev), t_history, head);
	else
		while (hist && ((!i && hist->head.next) || (i && hist->head.prev))
		&& hist->value)
			if (ft_strnequ(hist->value, new_value, ft_strlen(new_value)))
				break ;
			else if (i)
				hist = (!(hist)->head.prev) ? NULL :
				GET_NODE(((hist)->head.prev), t_history, head);
			else
				hist = (!(hist)->head.next) ? NULL :
				GET_NODE(((hist)->head.next), t_history, head);
	ft_memdel((void **)&new_value);
	if (hist && hist->value)
		return (hist->value);
	return (NULL);
}

static int		get_hist_idx(t_shell *sh, t_parser *p, char *key)
{
	char		*new_value;
	char		*str;
	int			idx;

	str = NULL;
	if (!(new_value = NULL) && key[1] == '!' && !key[2])
		str = GET_NODE(list_last(&sh->history->head), t_history, head)->value;
	idx = ft_atoi(&key[1]);
	if (!str && (ft_isdigit(key[1]) || key[1] == '-')
	&& (idx == 0 || ft_abs(idx) > (int)list_len(&sh->history->head)))
		return (1);
	if (!str)
	{
		if (!(new_value = ft_strdup(&key[1])))
			return (1);
		str = get_str_hist(sh, ft_abs(idx), new_value,
		(!idx || (ft_abs(idx) != idx)) ? 1 : 0);
	}
	if (str)
	{
		handle_aliases(p, key, str);
		ft_fdprintf(1, "%s\n", p->orig);
		ft_memdel((void **)&key);
	}
	return (str) ? (0) : (1);
}

char			*handle_first_word(t_shell *sh, t_parser *p)
{
	int			idx;
	t_cell		*cell;
	char		*ret;
	char		*key;

	idx = FWD(CURRENT(p)) - CURRENT(p) + p->idx;
	if (!(p->first_word = 0) && p->orig[idx] == '=')
	{
		ret = implicit_parse_one(sh, p);
		add_state(&(p->states), ST_SETVAR);
		return (ret);
	}
	else if ((key = ft_strsub(p->orig, p->idx, idx - p->idx)) != NULL &&
	(cell = dict_get(p->opts->aliases, key)) != NULL && !p->aliases_done)
	{
		handle_aliases(p, key, cell->value);
		p->aliases_done = 1;
		ft_memdel((void **)&key);
		return (NULL);
	}
	else if (key[0] == '!' && key[1] && !get_hist_idx(sh, p, key))
		return (NULL);
	ft_memdel((void **)&key);
	p->aliases_done = 0;
	return (handle_normal(sh, p));
}
