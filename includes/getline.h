/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoreilh <amoreilh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 11:22:22 by amoreilh          #+#    #+#             */
/*   Updated: 2017/04/10 17:24:00 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETLINE_H
# define GETLINE_H
# include <unistd.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdlib.h>
# include <termios.h>
# include <term.h>
# include <sys/types.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <fcntl.h>

/*
**	Size of Buffers
*/
# define READBUFSIZE 8
# define BUFFSIZE 64
# define PROMPTBUF 512

/*
**	Define Size of Function Pointer Array
*/
# define NB_TERM_COMMAND_CURSOR		18
# define NB_TERM_COMMAND_EDITION	6

/*
**	Print mode
*/
# define NO_ACTION					1
# define CURSOR_O					2
# define PRINT_O					3
# define PRINT_AND_CURSOR			4

/*
**	End line edition capacities
*/
# define CAPS_CTRL_C				3
# define CAPS_CTRL_D				4
# define CAPS_ENTER					10

/*
**	Edit line edition capacities
*/
# define CAPS_CTRL_K				11
# define CAPS_CTRL_L				12
# define CAPS_CTRL_U				21
# define CAPS_CTRL_X				24
# define CAPS_CTRL_Y				25
# define CAPS_BSPACE				127
# define CAPS_DEL					2117294875

/*
**	Cursor moves capacities
*/
# define CAPS_CTRL_A				1
# define CAPS_CTRL_E				5
# define CAPS_TAB					9
# define CAPS_ARROW_UP				4283163
# define CAPS_ARROW_DOWN			4348699
# define CAPS_ARROW_RIGHT			4414235
# define CAPS_ARROW_LEFT			4479771
# define CAPS_END					4610843
# define CAPS_HOME					4741915
# define CAPS_ALT_UP				1096489755
# define CAPS_ALT_DOWN				1113266971
# define CAPS_ALT_RIGHT				1130044187
# define CAPS_ALT_LEFT				1146821403
# define CAPS_ALT_UP_LINUX			71688292227867
# define CAPS_ALT_DOWN_LINUX		72787803855643
# define CAPS_ALT_RIGHT_LINUX		73887315483419
# define CAPS_ALT_LEFT_LINUX		74986827111195

typedef struct		s_starmatch
{
	char			*path;
	char			*word;
	int				wordlen;
	int				pathlen;
	int				wordpos;
}					t_starmatch;

typedef struct		s_input
{
	char			end;
	char			*line;
	char			*current_line;
	int				buffsize;
	char			multi;
	char			comp;
	char			prompt;
	char			*prompt2;
	char			cursbuff[12];
	char			*clipboard;
	int				bufx;
	int				bufxmax;
	int				bufposmax;
	int				bufy;
	int				bufpos;
	int				termw;
	int				termh;
	int				cursx;
	int				cursy;
	int				prompt2len;
	int				savecursx;
	int				savecursy;
	int				nblines;
	int				ret;
}					t_input;

void				ft_displaypromptline(t_input *input);
void				creat_new_term_struct(struct termios *new,
						struct termios *old);
char				hist_comphist(t_input *input, t_shell *sh, char upndown);
char				*ft_getbranch(void);
void				ft_freematch(t_starmatch *match);
int					ft_nblines(t_input *input);
char				*linedit_reallocbuff(t_input *input);
void				ft_getmatchingfiles(t_input *input);
void				ft_checkdir(t_starmatch *match, t_input *input);
t_starmatch			*ft_getword(int pos, char *line, t_input *input);

void				ft_cursgoto(int x, int y, int fd);
void				ft_getcurscoords(t_input *input, t_shell *sh);
int					term_setterm(t_shell *sh);
int					term_resetterm(t_shell *sh);
int					term_isfolder(char *path);
void				ft_prompt(t_input *input, t_shell *sh);

int					linedit_printchar(t_input *input, char *buf, char *line);

char				*ft_getline(t_input *input, t_shell *sh);

int					arrow_left(t_input *input);
int					arrow_right(t_input *input);
int					alt_arrow_up(t_input *input);
int					alt_arrow_down(t_input *input);
int					home_position(t_input *input);
int					end_position(t_input *input);

int					linedit_cut(t_input *input);
int					linedit_cut_all_line(t_input *input);
int					linedit_paste(t_input *input);

int					linedit_del(t_input *input);
int					linedit_bspace(t_input *input);

int					previous_word(t_input *input);
int					next_word(t_input *input);

int					bridge_tab(t_input *input);
int					bridge_up(t_input *input);
int					bridge_down(t_input *input);
int					bridge_maj_down(t_input *input);

int					ft_putc(int c);
void				print_special_putstr_fd(char *str, int fd);

char				*ft_histsearch(t_input *input, t_shell *sh);
int					put_stdout(char *c);
char				event_loop(t_shell *sh, char **ptr);

int						(*g_term_command_cursor[NB_TERM_COMMAND_CURSOR])
															(t_input *input);
int					(*g_term_command_edition[NB_TERM_COMMAND_EDITION])
															(t_input *input);

#endif
