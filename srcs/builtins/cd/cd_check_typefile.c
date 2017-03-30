/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_check_typefile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrosa <qrosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 16:44:46 by qrosa             #+#    #+#             */
/*   Updated: 2017/02/22 20:11:38 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	cd_check_typefile(mode_t mode)
{
	if (mode == S_IFREG)
		return ('-');
	if (mode == S_IFDIR)
		return ('d');
	if (mode == S_IFLNK)
		return ('l');
	if (mode == S_IFSOCK)
		return ('s');
	if (mode == S_IFIFO)
		return ('p');
	if (mode == S_IFBLK)
		return ('b');
	if (mode == S_IFCHR)
		return ('c');
	return ('?');
}
