/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulaye <nboulaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 16:49:16 by nboulaye          #+#    #+#             */
/*   Updated: 2017/02/24 19:10:12 by qrosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>

typedef struct s_shell	t_shell;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

long int			ft_atoi(const char *src);
void				ft_bzero(void *s, size_t n);
void				*ft_free_line(char **line);
char				**ft_free_tab(char **mytab);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isnumber(char *str);
int					ft_isprint(int c);
int					ft_isspace(int c);
char				*ft_itoa(int n);
char				*ft_itoa_base(long double value, int base);
int					ft_itoa_base_buffer(long double val, int base, char *buf);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(const void *content, size_t content_size);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *str, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *s, int c, size_t n);
size_t				ft_min(size_t a, size_t b);
int					ft_putchar(char c);
int					ft_putendl(const char *s);
void				ft_putnbr(int n);
int					ft_putstr(const char *s);
void				ft_putnstr(const char *s, int i);
void				ft_putnstr_fd(const char *s, int i, int fd);
void				ft_putnbrstr(int nbr, char *s1);
int					ft_putnbrstr_fd(int nbr, char *s1, int fd);
void				ft_putstrstrstr(char *s1, char *s2, char *s3);
int					ft_putstrcharstr_fd(char *s1, char c, char *s2, int fd);
void				ft_putstrnbrstr(char *s1, int nbr, char *s2);
int					ft_putstrnbrstr_fd(char *s1, int nbr, char *s2, int fd);
void				ft_putstrstr(char *s1, char *s2);
int					ft_putstrstr_fd(char *s1, char *s2, int fd);
void				ft_putstrnbr(char *s1, int nbr);
int					ft_putstrnbr_fd(char *s1, int nbr, int fd);
void				ft_putchar_fd(char c, int fd);
int					ft_putendl_fd(const char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_putstr_fd(const char *s, int fd);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *s1, size_t n);
int					ft_strequ(const char *s1, const char *s2);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strnjoin(const char *s1, const char *s2, size_t i);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *str);
int					ft_strcnlen(char *str, char c, int n);
char				*ft_strmap(const char *s, char (*f)(char));
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t n);
int					ft_strnequ(const char *s1, const char *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
char				*ft_strrchr(const char *s, int c);
char				*ft_strrnchr(const char *s, int c, size_t max);
char				**ft_strsplit(const char *s, char c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strsub(const char *s, unsigned int star, size_t len);
char				*ft_strtrim(const char *s);
char				*ft_strntrim(const char *s, size_t len);
size_t				ft_tablen(char **mytab);
void				ft_tabstrdel(char **t);
char				*ft_strtolower(char *str);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_abs(int i);
void				ft_capitaliz(char *str);
void				ft_freetab(char ***t);
void				ft_cleanscr(void);

#endif
