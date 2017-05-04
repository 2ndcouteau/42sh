NAME = libft.a

SRCSPATH = ft_printf/
OPT_PATH = opt_parse_arg/
LIBFT_INCLUDES = includes

SR =	ft_printf.c\
		flags.c\
		read_arg.c\
		do_d.c\
		do_f.c\
		do_u.c\
		do_o.c\
		do_x.c\
		do_p.c\
		do_c.c\
		do_b.c\
		do_ls.c\
		do_s.c\
		do_not_specifier.c

SRCL =	ft_putchar.c\
		ft_putstr.c\
		ft_putnstr.c\
		generic_print.c\
		generic_fd_print.c\
		ft_putnbr.c\
		ft_strclr.c\
		ft_memalloc.c\
		ft_memset.c\
		ft_bzero.c\
		ft_strdup.c\
		ft_strndup.c\
		ft_strcpy.c\
		ft_strncpy.c\
		ft_strcat.c\
		ft_strncat.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strrnchr.c\
		ft_strcmp.c\
		ft_strlen.c\
		ft_strcnlen.c\
		ft_strncmp.c\
		ft_atoi.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_isnumber.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_isspace.c\
		ft_itoa.c\
		ft_itoa_base.c\
		ft_itoa_base_buffer.c\
		ft_strstr.c\
		ft_strnstr.c\
		ft_strequ.c\
		ft_strnequ.c\
		ft_strnew.c\
		ft_memdel.c\
		ft_strdel.c\
		ft_memcpy.c\
		ft_memccpy.c\
		ft_memmove.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_putendl.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_strlcat.c\
		ft_strsub.c\
		ft_strjoin.c\
		ft_strnjoin.c\
		ft_tablen.c\
		ft_strtrim.c\
		ft_strntrim.c\
		ft_strsplit.c\
		ft_striter.c\
		ft_striteri.c\
		ft_strmap.c\
		ft_strmapi.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strtolower.c\
		ft_lstnew.c\
		ft_lstadd.c\
		ft_lstdelone.c\
		ft_lstdel.c\
		ft_lstiter.c\
		ft_lstmap.c\
		ft_tabstrdel.c\
		ft_min.c\
		ft_abs.c\
		ft_cleanscr.c\
		ft_capitaliz.c\
		get_next_line.c\
		ft_free_tab.c\
		ft_free_line.c

OPT =	opt_check_options.c\
		opt_exist_letter.c\
		opt_exist_long.c\
		opt_free_end.c\
		opt_get_options.c\
		opt_init_env.c\
		opt_is_valid.c\
		opt_parse_arguments.c\
		opt_print_error.c\
		opt_save_arg.c\
		opt_check_last_opt.c

SRC =	$(SRCL)\
		$(addprefix $(SRCSPATH), $(SR))\
		$(addprefix $(OPT_PATH), $(OPT))\

WFLAGS = -Wall -Werror -Wextra

LFLAGS = -L libft/ -lft

CC = gcc #-g -ggdb

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o: %.c
	@$(CC) -c $(WFLAGS) -I $(LIBFT_INCLUDES)  $< -o $@

$(NAME) : $(OBJ)
	@echo 'compilation libft'
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo ' - - - - - - ok'

clean :
	@echo "CLEAN LIBFT"
	@rm -rf $(OBJ)

fclean : clean
	@echo "FCLEAN LIBFT"
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
