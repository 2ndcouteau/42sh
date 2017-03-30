/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 21:59:04 by nboulaye          #+#    #+#             */
/*   Updated: 2017/01/19 12:28:02 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "list_head.h"
# include "processes.h"

enum
{
	REDIN,
	REDOUT,
	REDAPPEND,
	HEREDOC,
};

void	debug_redir(t_redir *red);
int		redir(t_processes *proc, int fd[4]);
int		chk_redir(t_redir *red);
int		redir_in(t_redir *red);
int		redir_out(t_redir *red, int append);
int		redir_heredoc(t_redir *red);
void	close_redir(t_redir *red);

#endif
