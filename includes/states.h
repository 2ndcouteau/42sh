/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 15:47:59 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/15 16:28:38 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATES_H
# define STATES_H

# include "list_head.h"

typedef struct				s_states
{
	int						state;
	t_head					head;
}							t_states;

t_states					*new_state(int state);
void						push_state(t_states **stack, int state);
void						repl_state(t_states **stack, int state);
void						add_state(t_states **stack, int state);
void						pop_state(t_states **stack);
void						destroy_states(t_states **states);

#endif
