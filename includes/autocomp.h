/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 11:22:22 by amoreilh          #+#    #+#             */
/*   Updated: 2017/04/10 17:24:33 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMP_H
# define AUTOCOMP_H
# define I input
# define A autoc

typedef struct	s_compnode
{
	char		*word;
	int			index;
	int			padding;
	int			wordlen;
	char		isover;
	t_head		head;
}				t_compnode;

typedef struct	s_autocomp
{
	char		*str;
	DIR			*dir;
	int			len;
	int			i;
	int			nbwperline;
	char		*path;
	int			pathlen;
	int			nblines;
	int			nbwords;
	int			maxwlen;
	char		*choice;
	t_compnode	*first;
}				t_autocomp;

void			ft_initstruct(t_input *input, t_shell *sh);
char			*ft_initreadline(t_input *input, t_shell *sh,
					t_autocomp *autoc);

void			ft_getlistsize(t_autocomp *autoc, t_input *input);
void			ft_folderorglob(t_autocomp *autoc, t_input *input);
void			ft_getfolder(t_autocomp *autoc, t_input *input);
int				ft_insertmatch(char *wd, t_starmatch *match, int p,
	t_input *input);
void			ft_getmatchforlder(t_starmatch *match);

int				linedit_inputkeyhook(t_input *input, t_autocomp *autoc,
					char *buf);
int				linedit_command_cursor(t_input *input, long int *buff_convert);
int				linedit_command_edition(t_input *input, long int *buff_convert);

int				ft_endgetlineloop(t_shell *sh, t_input *input,
					t_autocomp *autoc);
void			getline_put_line(t_input *input, char *buf, t_shell *sh,
					t_autocomp *autoc);
int				getline_loop(t_shell *sh, t_input *input, char *buf,
					t_autocomp *autoc);

void			ft_printbuf(t_input *input, t_autocomp *autoc);
int				ft_isfirstword(t_input *input, char *line);
char			*comp_firstletters(t_input *input);
int				ft_complines(t_autocomp *autoc, t_input *input);
void			ft_freecomplist(t_autocomp *autoc);
void			ft_displaycomplist(t_autocomp *autoc, t_input *input);
void			ft_getlist(t_autocomp *autoc);
int				comp_autocomp(t_input *input, t_autocomp *autoc);
void			ft_dispcomp(t_autocomp *comp, t_input *input);
t_compnode		*ft_makecompnode(char *name);
int				linedit_clear(t_input *input, t_autocomp *autoc);

#endif
