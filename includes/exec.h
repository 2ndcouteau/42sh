/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 18:55:46 by nboulaye          #+#    #+#             */
/*   Updated: 2017/04/26 19:38:46 by ljohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "shell.h"

int		g_debug[2];

void	printarg(t_processes *proc, char *str, int fd);
void	debug(int n, char *path);

void	readcmd(char *cmd, t_shell *sh, char *tmppath, char **pathcmp);

void	wait_bg(t_jobs **jobs_lst, t_jobs *jobs);
void	ft_execjobs(t_shell *sh, t_jobs *jobs, t_dict *env, int preflag);
void	ft_execprocess(t_jobs **jobs, t_processes *proc,
		t_shell *sh, t_dict *env);
void	exec_dad(t_jobs **jobs, t_shell *sh, t_processes *proc, int fd[4]);
void	wait_process(t_processes *proc, t_jobs **jobs, t_jobs **bg_jobs
		, t_shell *sh);
int		creat_pipe(int fd[4]);

void	chk_status(int status);
void	sav_stopped_jobs(t_jobs **bg_jobs_lst, t_jobs **jobs, int stopped);
void	del_stopped_jobs(t_jobs **bg_jobs_lst, pid_t pgid);
int		ft_isbuiltin(char *name);
int		execbuiltin(t_shell *sh, t_processes *proc, int idx_builtin);
int		get_idx_bg_jobs(char **argv, t_jobs **bg_jobs);

char	*get_code(char *str, int *idxs);
char	*get_eval(t_shell *shell, char *code);

int		replace_subshells(t_shell *shell, t_processes **proc);

void	child_eval(int fds_out[2], t_shell *shell);

#endif
