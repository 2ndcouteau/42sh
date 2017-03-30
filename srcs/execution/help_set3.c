/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_set3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohan <ljohan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 17:50:43 by ljohan            #+#    #+#             */
/*   Updated: 2017/02/24 17:41:56 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		help_set_set(t_dict *help)
{
	dict_set(help, new_cell(
		ft_strdup("set"),
		new_help(
			"set",
			"set [<key> [<value>]]",
			"set local variables."),
		&free));
}

void		help_set_unset(t_dict *help)
{
	dict_set(help, new_cell(
		ft_strdup("unset"),
		new_help(
			"unset",
			"unset <key>",
			"delete local variables."),
		&free));
}

void		help_set_echo(t_dict *help)
{
	dict_set(help, new_cell(
		ft_strdup("echo"),
		new_help("echo",
		"echo [-neE] [arg ...]",
"Output the ARGs.  If -n is specified, the trailing newline is\
	\n\tsuppressed. Interpretation of the following backslash-escaped\
	\n\tcharacters with -e:\
	\n\t\t\\a      alert (bell)\
	\n\t\t\\b      backspace\
	\n\t\t\\c      suppress trailing newline\
	\n\t\t\\e      escape character\
	\n\t\t\\E      escape character\
	\n\t\t\\f      form feed\
	\n\t\t\\n      new line\
	\n\t\t\\r      carriage return\
	\n\t\t\\t      horizontal tab\
	\n\t\t\\v      vertical tab\
	\n\t\t\\\\     backslash"),
		&free));
}

void		help_set_cd(t_dict *help)
{
	dict_set(help, new_cell(
		ft_strdup("cd"),
		new_help(
			"cd",
			"cd [-LP] [directory]",
			"Change Directory - change the current working directory to a\
			\n\tspecific Folder.\
			\n-P\tDo not follow symbolic links\
			\n-L\tollow symbolic links (default)\
			\n\n\t If directory is given, changes the shell's working\
			\n\tdirectory to directory. If not, changes to $HOME.\
			\n\t If directory is '-', this will change to the previous\
			\n\tdirectory location (equivalent to $OLDPWD).\
			\n\t If directory starts by '~', this will replace by $HOME and\
			\n\tjoin with the rest of your path."),
		&free));
}
