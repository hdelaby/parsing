# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/05 13:43:29 by hdelaby           #+#    #+#              #
#    Updated: 2017/03/30 10:58:41 by hdelaby          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBDIR = libft/
LIBNAME  = libft/libft.a
LIBFLAGS = -Llibft -lft -ltermcap

INC= -I./includes -I./libft/includes

SRC_PATH = src/
VPATH = .: src/line_edition src/parsing src/lexing src/execution src/builtin \
	src
SRC_NAME = handlers_operands.c\
		   handlers_other.c\
		   lexer.c\
		   lexing_tools.c\
		   parser.c\
		   manip_env.c\
		   grammar_elem.c\
		   ast.c\
		   astdel.c\
		   explore_tree.c\
		   exec_pipe.c\
		   exec_redir.c\
		   exec_cmd.c\
		   restore_fd.c\
		   get_key.c\
		   ft_getwinsz.c\
		   tc_putc.c\
		   line_editing.c\
		   set_term_mode.c\
		   get_input.c\
		   cursor_motion.c\
		   content_navigation.c\
		   history.c\
		   ft_dlstsize.c\
		   ft_dlstdelstr.c\
		   signal_handling.c\
		   bi_setenv.c\
		   bi_unsetenv.c\
		   bi_cd.c\
		   bi_cd_extra.c\
		   bi_exit.c\
		   bi_echo.c\
		   error_handling.c\
		   main.c

OBJ_PATH = obj/
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

all: $(NAME)

run: all
	@make run -C unit_test

$(NAME): $(OBJ)
	@make all -C libft
	@$(CC) $(LIBFLAGS) $(INC) -o $@ $^
	@echo "\033[32m$(NAME) created successfully\033[0m"

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -sC libft

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBNAME)

re: fclean all

.NOTPARALLEL: re
.PHONY: all clean fclean re
