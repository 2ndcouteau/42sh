/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 13:10:53 by ljohan            #+#    #+#             */
/*   Updated: 2017/01/21 17:58:19 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "dict.h"

void		help_set_help(t_dict *help)
{
	dict_set(help, new_cell(
		ft_strdup("help"),
		new_help(
			"help",
			"help [<name> ...]",
			"print help on function or builtin <name>.\
			\n\tIf <name> not provided, print short help on all avaible help"),
		&free));
}

void		help_set_env(t_dict *help)
{
	dict_set(help, new_cell(
		ft_strdup("env"),
		new_help(
			"env",
			"env [-i] [-u name] [name=value ...]",
			"set environment and execute command, or print environment\
			\n\tThe env utility executes another utility after modifying the\
			\n\tenvironment as specified on the command line.  Each name=value\
			\n\toption specifies the setting of an environment variable, name,\
			\n\twith a value of value.  All such environment variables are set\
			\n\tbefore the utility is executed.\
			\n\n-i\tExecute the utility with only those environment variables\
			\n\tspecified by name=value options.  The environment inherited\
			\n\tby env is ignored completely.\
			\n\n-u name\tIf the environment variable name is in the env,\
			\n\tthen remove it before processing the remaining options"),
		&free));
}

void		help_set_setenv(t_dict *help)
{
	dict_set(help, new_cell(
		ft_strdup("setenv"),
	new_help(
		"setenv",
		"setenv <key> [<value>]",
		"set the environment variable <key> with the value <value>."),
	&free));
}

void		help_set_fg(t_dict *help)
{
	dict_set(help, new_cell(
	ft_strdup("fg"),
	new_help(
		"fg",
		"fg [job_spec]",
		"Place JOB_SPEC in the foreground, and make it the current job. If\
		\n\tJOB_SPEC is not present the shell's notion of the current job is\
		\n\tused."),
	&free));
}

void		help_set_bg(t_dict *help)
{
	dict_set(help, new_cell(
	ft_strdup("bg"),
	new_help(
		"bg",
		"bg [job_spec]",
		"Place each JOB_SPEC in the background, as if it had been started with\
		\n\t`&'.  If JOB_SPEC is not present, the shell's notion of the current\
		\n\tjob is used."),
	&free));
}
