/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:38:43 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/24 16:44:16 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

/*
** foreground colors
*/

# define F_RED "\033[0;31m"
# define F_GRE "\033[0;32m"
# define F_YEL "\033[0;33m"
# define F_BLU "\033[0;34m"
# define F_CYA "\033[0;36m"
# define F_END "\033[0;39m"

void	debug_states(t_states *states);
void	debug_parser(t_parser *parser);
void	debug_flags(int flag);
void	debug_dict(t_dict *dict);
char	*human_state(int state);
void	debug_process(t_processes *proc);

#endif
