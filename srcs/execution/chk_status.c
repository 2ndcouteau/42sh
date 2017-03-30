/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/10 03:47:51 by nboulaye          #+#    #+#             */
/*   Updated: 2017/01/19 12:30:13 by nboulaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void		chk_status3(int status)
{
	if (status == 24)
		ft_putstr_fd("\t\033[31mcpu time limit exceeded\033[0m\t", 2);
	else if (status == 25)
		ft_putstr_fd("\t\033[31mfile size limit exceeded\033[0m\t", 2);
	else if (status == 26)
		ft_putstr_fd("\t\033[31mvirtual time alarm\033[0m\t", 2);
	else if (status == 27)
		ft_putstr_fd("\t\033[31mprofiling timer alarm\033[0m\t", 2);
}

static void		chk_status2(int status)
{
	if (status > 22)
		chk_status3(status);
	else if (status == 12)
		ft_putstr_fd("\t\033[31mnon-existent system call invoked\033[0m\t", 2);
	else if (status == 13)
		ft_putstr_fd("\t\033[31mwrite on a pipe with no reader\033[0m\t", 2);
	else if (status == 14)
		ft_putstr_fd("\t\033[31malarm\033[0m\t", 2);
	else if (status == 15)
		ft_putstr_fd("\t\033[31mterminated\033[0m\t", 2);
	else if (status == 17)
		ft_putstr_fd("\t\033[31mXXXterminated\033[0m\t", 2);
	else if (status == 18)
		ft_putstr_fd("\t\033[31mstop sig. generated from keyboard\033[0m\t", 2);
	else if (status == 19)
		ft_putstr_fd("\t\033[31mXXXterminated\033[0m\t", 2);
	else if (status == 20)
		ft_putstr_fd("\t\033[31mXXXterminated\033[0m\t", 2);
	else if (status == 21)
		ft_putstr_fd("\t\033[31msuspended (tty input)\033[0m\t", 2);
	else if (status == 22)
		ft_putstr_fd("\t\033[31msuspended (tty output)\033[0m\t", 2);
}

void			chk_status(int status)
{
	if (status > 11)
		chk_status2(status);
	else if (status == 1)
		ft_putstr_fd("\t\033[31mterminal line hangup\033[0m\t", 2);
	else if (status == 2)
		ft_putstr_fd("\t\033[31minterrupt\033[0m\t", 2);
	else if (status == 3)
		ft_putstr_fd("\t\033[31mquit\033[0m\t", 2);
	else if (status == 4)
		ft_putstr_fd("\t\033[31m illegal instruction\033[0m\t", 2);
	else if (status == 5)
		ft_putstr_fd("\t\033[31mtrace trap\033[0m\t", 2);
	else if (status == 6)
		ft_putstr_fd("\t\033[31mabort\033[0m\t", 2);
	else if (status == 7)
		ft_putstr_fd("\t\033[31memulate instruction executed\033[0m\t", 2);
	else if (status == 8)
		ft_putstr_fd("\t\033[31mfloating-point exception\033[0m\t", 2);
	else if (status == 9)
		ft_putstr_fd("\t\033[31mkill program\033[0m\t", 2);
	else if (status == 10)
		ft_putstr_fd("\t\033[31mbus error\033[0m\t", 2);
	else if (status == 11)
		ft_putstr_fd("\t\033[31msegmentation violation\033[0m\t", 2);
}
