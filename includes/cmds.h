/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 15:50:04 by ljohan            #+#    #+#             */
/*   Updated: 2016/11/25 08:27:30 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H

# include "list_head.h"

typedef struct	s_cmds
{
	char		**argv;
	t_head		head;
}				t_cmds;

t_cmds			*new_cmds(void);
void			destroy_cmds(t_cmds **cmds);
t_cmds			*get_last_cmd(t_cmds *cmd);

#endif
