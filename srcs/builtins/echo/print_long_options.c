/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_options.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:14:58 by qrosa             #+#    #+#             */
/*   Updated: 2017/02/21 19:10:11 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	print_help(void)
{
	ft_putendl("Usage: echo [SHORT-OPTION]... [STRING]...\n  or:  echo LON\
G_OPTION\nEcho the STRING(s) to standard output\n\n  -n		do not output the t\
railing newline\n  -e		enable interpretation of backslash escapes\n  -E\
		disable interpretation of backslash escapes (default)\n  --help	dis\
play this help and exit\n  --version	output version information and exit\n\n\
If -e is in effect, the following sequences are recognized:\n\n  \\\\ 	backsla\
sh\n  \\a	alert (BEL)\n  \\b	backspace\n  \\c 	produce no further output\n\
\\e	escape\n  \\f 	form feed\n  \\n 	new line\n  \\r 	carriage return\
\n  \\t 	horizontal tab\n  \\v 	vertical tab\n  \\0NNN	byte with octal val\
ue NNN (1 to 3 digits)\n  \\xHH	byte with hexadecimal value HH (1 to 2 digits)"
);
}

static void	print_version(void)
{
	ft_putendl("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\
$     Version of builtin echo for 42sh      $\n\
$                                           $\n\
$              -- One love --               $\n\
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
);
}

bool		print_long_options(short options)
{
	if ((options & 4) == 4)
	{
		print_help();
		return (SUCCESS);
	}
	else if ((options & 8) == 8)
	{
		print_version();
		return (SUCCESS);
	}
	return (ERROR);
}
