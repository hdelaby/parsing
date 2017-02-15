# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/05 13:43:29 by hdelaby           #+#    #+#              #
#    Updated: 2017/02/15 11:20:47 by hdelaby          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= parsing
CC= gcc
CFLAGS= -Wall -Wextra -Werror

LIBDIR= libft/
LIBNAME = libft/libft.a
LIBFLAGS= -Llibft -lft

INC= -I./includes -I./libft/includes

SRC_PATH = src
SRC_NAME = main.c\
		   prompt.c\
		   parsing.c\
		   execution.c\
		   getters.c\
		   bi_echo.c\
		   bi_cd.c\
		   bi_cd_extra.c\
		   bi_env.c\
		   bi_exit.c\
		   bi_setenv.c\
		   bi_unsetenv.c\
		   signal_handling.c\
		   error_handling.c\
		   manip_env.c\
		   manip_env_tools.c\
		   ft_canon_path.c

OBJ_PATH = obj
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@make all -C libft
	@$(CC) $(LIBFLAGS) $(INC) -o $@ $^
	@echo "\033[32m$(NAME) created successfully\033[0m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -sC libft

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBNAME)

re: fclean all
