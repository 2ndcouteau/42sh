/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:32:09 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/23 18:16:12 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICT_H
# define DICT_H

# include "list_head.h"

typedef struct	s_cell
{
	char		*key;
	void		*value;
	void		(*del_value)(void*);
	t_head		head;
	int			dbg;
}				t_cell;

typedef struct	s_dict
{
	t_cell		**cells;
	size_t		size;
}				t_dict;

int				key_hash(char *key);
char			cmp_cell_keys(t_head *head, void *key);
t_cell			*dict_pop(t_dict *dict, char *key);
t_cell			*dict_next(t_dict *d, t_cell *cur);
void			dict_set_doublon(t_dict *dict, t_cell *cell);
void			print_str_dict(t_dict *dct);

t_cell			*new_cell(char *key, void *value, void (*del_value)(void*));
t_dict			*new_dict(size_t dsize);
void			dict_set(t_dict *dict, t_cell *cell);
void			destroy_dict(t_dict **dict);

t_cell			*dict_get(t_dict *dict, char *key);
size_t			dict_len(t_dict **dict);
void			dict_iter(t_dict *dict, void (*fct)(t_head *));
t_cell			*new_cell_wthout_malloc(char *key, void *value, size_t nb);
void			dict_iter(t_dict *dict, void (*fct)(t_head *));

t_head			*list_pop_last(t_head *head);
void			dict_del(t_dict *dict, char *key);
void			del_cell(t_cell **cell);
void			del_str_value(void *val);
char			**dict2env(t_dict *dict);
t_dict			*env2dict(char **env);
t_dict			*createbin_hashtab(char *path);
void			put_key_value(t_head *elem);

t_dict			*cpy_dict_env(t_dict *dict);
void			push_cell(t_cell **cells, t_cell *cell);

#endif
