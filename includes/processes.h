/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 15:49:01 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/28 16:58:30 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSES_H
# define PROCESSES_H

# include "list_head.h"
# include "dict.h"
# include "cmds.h"

typedef struct s_subshell	t_subshell;
struct			s_subshell
{
	int			idx;
	int			**instring;
	t_head		head;
};

typedef struct	s_redir
{
	t_head		head;
	char		*fdin;
	char		*arg;
	int			rtype;
	int			sav_fd;
	int			new_fd;
	int			fd_to_redir;
	char		*heredoc;
	char		heredoc_done;
}				t_redir;

typedef struct	s_processes
{
	t_head		head;
	t_cmds		*cmds;
	char		*path;
	pid_t		pid;
	t_dict		*env;
	char		complete;
	int			status;
	t_redir		*redir;
	t_subshell	*subshell;
}				t_processes;

t_processes		*new_processes(void);
t_processes		*get_last_process(t_processes *proc);
t_processes		*get_new_process(t_processes **proc);

t_subshell		*new_subshell(int idx);
int				add_subshell_idx(t_subshell **sub, int idx);
void			destroy_processes(t_processes **proc);

#endif
