/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 18:55:46 by nboulaye          #+#    #+#             */
/*   Updated: 2017/04/01 22:42:00 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H
# include "shell.h"
# define HIST_SIZE 8000

typedef struct	s_history
{
	char		*key;
	char		*value;
	t_head		head;
}				t_history;

t_history		*new_history_list(t_dict *env);
void			add_history(char *line, t_history **history);
char			*get_history(t_shell *sh, char *buf, int pos, char c);
void			destroy_history(t_history *hist);
int				open_read_f_history(t_history *history, t_dict *env);
int				creat_elem_hist(char *line, t_history *history);
int				strchr_replace(char *str, char c_old, char c_new);
int				open_read_f(t_dict *env);
char			hist_move(t_input *input, unsigned long *buff_conv);

#endif
