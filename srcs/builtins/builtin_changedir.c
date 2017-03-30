/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_changedir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 20:47:44 by qrosa             #+#    #+#             */
/*   Updated: 2017/03/22 16:21:40 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char		**cd_init_define(void)
{
	char	**mytab;

	if (!(mytab = (char**)malloc(sizeof(char*) * 7)))
		return (NULL);
	mytab[0] = ft_strdup("cd");
	mytab[1] = ft_strdup("-LP");
	mytab[2] = ft_strdup("");
	mytab[3] = ft_strdup(" [-L|-P]");
	mytab[4] = ft_strdup("");
	mytab[5] = ft_strdup("[dir]");
	mytab[6] = NULL;
	return (mytab);
}

void			exec_cd(t_cmd *current_cmd, t_dict *env, t_opt **cd_opt)
{
	char	*current_pwd;

	current_pwd = ft_memalloc(PATH_MAX);
	getcwd(current_pwd, PATH_MAX);
	cd_create_path_name(current_cmd, env, cd_opt, &current_pwd);
	if (current_cmd->error_nbr != 0)
	{
		cd_print_error(current_cmd->error_nbr,
	current_cmd->error_name);
	}
	else
	{
		chdir(current_pwd);
		cd_swap_pwd_env(env, &current_pwd, cd_opt);
	}
	current_pwd = ft_free_line(&current_pwd);
}

static void		*init_cmd(char **cmds)
{
	t_cmd	*new_cmd;

	if (!(new_cmd = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	new_cmd->split_line = cmds;
	new_cmd->size_split_line = ft_tablen(cmds);
	new_cmd->error_nbr = 0;
	new_cmd->error_name = NULL;
	return (new_cmd);
}

static t_cmd	*free_current_cmd(t_cmd *current_cmd)
{
	if (current_cmd != NULL)
	{
		if (current_cmd->error_name != NULL)
			free(current_cmd->error_name);
		current_cmd->error_name = NULL;
		current_cmd->split_line = NULL;
		free(current_cmd);
	}
	return (NULL);
}

int				ft_cd(char **cmds, t_dict *env)
{
	char	**cd_init;
	t_opt	*cd_opt;
	t_cmd	*current_cmd;
	int		error;

	current_cmd = NULL;
	if ((current_cmd = init_cmd(cmds)) == NULL)
		return (ERROR);
	cd_init = cd_init_define();
	cd_opt = opt_parse_arguments(current_cmd->size_split_line,\
	current_cmd->split_line, cd_init);
	if (cd_opt->mark != 2)
	{
		exec_cd(current_cmd, env, &cd_opt);
		opt_free(&cd_opt);
		error = current_cmd->error_nbr;
		current_cmd = free_current_cmd(current_cmd);
		if (error != 0)
			return (ERROR);
		return (SUCCESS);
	}
	opt_print_error(current_cmd->split_line, &cd_opt);
	opt_free(&cd_opt);
	current_cmd = free_current_cmd(current_cmd);
	return (ERROR);
}
