/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_set2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 13:10:53 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/17 11:59:23 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "dict.h"

void		help_set_unsetenv(t_dict *help)
{
	dict_set(help, new_cell(
		ft_strdup("unsetenv"),
		new_help(
			"unsetenv",
			"unsetenv [<key> ...]",
			"delete environment variables."),
		&free));
}

void		help_set_jobs(t_dict *help)
{
	dict_set(help, new_cell(
		ft_strdup("jobs"),
		new_help(
			"jobs",
			"jobs [-lp]",
			"Lists the active jobs. The -l option lists pid's in addition\
			\n\tto the normal information; the -p option lists pid's only.\
			\n\tWithout options, the status of all active jobs is printed."),
			&free));
}

void		help_set_alias(t_dict *help)
{
	dict_set(help, new_cell(
		ft_strdup("alias"),
		new_help(
			"alias",
			"alias [key] [value]",
			"With no arguments, prints current aliases,\
			\n\tif only a key is provided, delete the correspondig alias.\
			\n\tThe command is evaluated as an alias only for the first word."),
			&free));
}

void		help_set_unalias(t_dict *help)
{
	dict_set(help, new_cell(
		ft_strdup("unalias"),
		new_help(
			"unalias",
			"alias <key>",
			"unset an existing aliases"),
			&free));
}

void		help_set_history(t_dict *help)
{
	dict_set(help, new_cell(
		ft_strdup("history"),
		new_help(
			"history",
			"history [-c] [-d offset]",
			"Display the history list with line numbers.\
			\n\tThe `-d' option deletes the history entry at offset OFFSET.\
			\n\tThe `-c' option causes the history list to be\
			\n\tcleared by deleting all of the entries.\
			\nhistory expansion character:\
			\n\t!\tStart a history substitution\
			\n\t!n\tRefer to command line n.\
			\n\t!-n\tRefer to the command n lines back.\
			\n\t!!\tRefer to the previous command. This is a synonym for `!-1`.\
			\n\t!str\tRefer to the most recent command starting with str."),
			&free));
}
