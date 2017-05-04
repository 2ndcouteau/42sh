NAME = 42sh

CC = gcc
CCDBGF = #-g -ggdb
CCF = -Wextra -Werror -Wall

SRCS_NAMES = main.c script.c \
			\
			builtins/builtin_fg.c builtins/builtin_bg.c \
			builtins/builtin_env.c builtins/builtin_env_read_args.c\
			builtins/builtin_jobs.c \
			builtins/builtin_exit.c builtins/builtin_setenv.c \
			builtins/builtin_history.c builtins/builtin_history_print.c \
			builtins/builtin_alias.c builtins/builtin_set.c \
			builtins/builtin_echo.c builtins/echo/check_option_echo.c builtins/echo/check_option_is_valid.c builtins/echo/check_option_set.c \
			builtins/echo/convert_hex_octal_to_char.c builtins/echo/print_direct_line.c builtins/echo/print_echo_line.c \
			builtins/echo/print_long_options.c builtins/echo/print_special_line.c \
			builtins/builtin_changedir.c builtins/cd/cd_absolute_path.c builtins/cd/cd_check_new_path.c builtins/cd/cd_check_valid_file.c builtins/cd/cd_clean_path.c \
			builtins/cd/cd_create_path_name.c builtins/cd/cd_home.c builtins/cd/cd_oldpwd.c builtins/cd/cd_print_error.c builtins/cd/cd_relative_path.c \
			builtins/cd/cd_set_error.c builtins/cd/cd_swap_pwd_env.c builtins/cd/cd_add_end_path.c builtins/cd/cd_check_typefile.c \
			\
			linedit/put_stdout.c linedit/print_special_putstr_fd.c \
			linedit/tools.c linedit/autocomplist.c linedit/displayline.c \
			linedit/getline.c linedit/getline_loop.c linedit/getline_utils.c \
			linedit/getline_put_line.c \
			linedit/autocomp.c linedit/wildcards.c \
			linedit/linedit_inputkeyhook.c \
			linedit/linedit_del_supr_clear.c linedit/linedit_next_prev_word.c linedit/linedit_keys_arrows.c \
			linedit/linedit_copypaste.c linedit/linedit_printchar.c \
			linedit/linedit_command_cursor.c linedit/linedit_command_edition.c \
			linedit/linedit_home_end.c linedit/bridge_functions.c \
			linedit/comp_firstletters.c \
			linedit/hist_comphist.c \
			linedit/tools2.c linedit/termcaps.c \
			linedit/autocomptools.c linedit/wildcardutils.c \
			linedit/autocomptools2.c \
			\
			parser/list_head.c parser/states.c parser/ft_path.c parser/ft_stab.c \
			parser/list_head2.c parser/ft_stab2.c parser/ft_charat.c \
			parser/shell.c parser/parser.c parser/cmds.c parser/processes.c parser/jobs.c \
			parser/dict.c parser/dict2.c parser/dict3.c parser/dict4.c parser/dict5.c \
			parser/dict6.c  parser/ft_strjoinfree.c \
			parser/options.c parser/parse_redir.c parser/parse_redir2.c \
			parser/ft_stabjoin.c parser/normal.c parser/first_word.c parser/parser_main.c parser/parser_main_transition.c \
			parser/path_utils.c parser/handlers.c parser/parse_line.c parser/parse_utils.c \
			parser/last_elem.c parser/new_elem.c parser/current_redir.c parser/transitions.c \
			parser/transitions2.c parser/transitions3.c parser/parse.c parser/heredoc.c \
			parser/transition_string.c parser/handle_pipe.c parser/onemore.c \
			parser/handle_setvar.c parser/parse_sub.c parser/subshell.c parser/itab.c \
			parser/parse2.c parser/states2.c \
			\
			execution/chk_status.c execution/exec_proc.c \
			execution/wait_proc.c execution/creat_pipe.c execution/redir.c \
			execution/history.c execution/get_history.c execution/creat_history.c \
			execution/jobs_ctrl.c execution/wait_bg.c \
			execution/redirection.c \
			execution/help_set.c execution/help_set2.c execution/help_set3.c \
			execution/environ.c execution/help.c execution/chk_if_builtin.c \
			execution/exec_jobs.c execution/ft_eval.c execution/readcmd.c \
			execution/exec_sub_proc.c execution/exec_sub_proc2.c execution/child_eval.c \
			\
			debug/debug_parser.c debug/debug_parser2.c debug/debug_process.c \
			debug/debug_dicts.c debug/activ_debug.c

SRCS_PATH = ./srcs/
SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAMES))

OBJS_PATH = ./objs/
OBJS_NAMES = $(SRCS_NAMES:.c=.o)
OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAMES))

FT_PATH = ./libft/
FT_INC_NAMES = libft.h get_next_line.h
FT_INC_PATH = $(FT_PATH)includes/
FT_INC = $(addprefix $(FT_INC_PATH),$(FT_INC_NAMES))
FT_NAME = libft.a

HEADERS = 	autocomp.h \
			cmds.h \
			debug.h \
			dict.h \
			exec.h \
			getline.h \
			history.h \
			jobs.h \
			list_head.h \
			options.h \
			parser.h \
			processes.h \
			shell.h \
			builtins.h \
			states.h

INCLUDES = $(addprefix ./includes/, $(HEADERS))
INC = ./includes/

cfred = \033[0;31m
cfgre = \033[0;32m
cfyel = \033[0;33m
cfblu = \033[0;34m
cfcya = \033[0;36m
cfend = \033[0;39m

all: $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@echo "$(cfyel)making:$(cfcya) $@$(cfend)"
	@mkdir $(OBJS_PATH) $(OBJS_PATH)parser $(OBJS_PATH)linedit $(OBJS_PATH)debug $(OBJS_PATH)execution $(OBJS_PATH)builtins $(OBJS_PATH)builtins/echo $(OBJS_PATH)builtins/cd 2> /dev/null || echo "" > /dev/null
	@$(CC) $(CCDBGF) -I $(INC) -I $(FT_INC_PATH) -o $@ -c $<

$(NAME): $(OBJS) $(INCLUDES)
	@echo "$(cfyel)making:$(cfcya) libft$(cfend)"
	@make -C $(FT_PATH)
	@echo "$(cfyel)making:$(cfcya) 42sh$(cfend)"
	$(CC) $(CCDBGF) $(CCF) -o $(NAME) $(SRCS) -I $(INC) -I $(FT_INC_PATH) -L$(FT_PATH) -lft -ltermcap

clean:
	@make clean -C $(FT_PATH)
	@rm -rf $(OBJS_PATH)
	@rm -rf $(NAME).dSYM
	@rm -f ./a.out
	@rm -rf ./a.out.dSYM
	@rm -rf .DS_Store

fclean: clean
	@make fclean -C $(FT_PATH)
	@rm -f $(NAME)

re: fclean all

.PHONY: 	all clean fclean re test
