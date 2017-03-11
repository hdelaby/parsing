# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/05 13:43:29 by hdelaby           #+#    #+#              #
#    Updated: 2017/03/11 09:58:28 by hdelaby          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		test
NAME_PATH =	./
SRC_PATH =	./

VPATH = .:basic_command pipe_command
SRC_NAME =	main.c\
			\
			00_basic_cmd.c 01_bin_echo.c 02_bin_echo_opt_n.c\
			\
			00_pipe_cmd.c 01_pipe_one.c

OBJ_PATH =	./obj/
OBJ_NAME =	$(SRC_NAME:.c=.o)
INC = 	-I../framework/includes -I../libft/includes -I./

SRC =		$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ =		$(addprefix $(OBJ_PATH),$(OBJ_NAME))

CFLAGS =	-Wall -Werror -Wextra -c
CC = gcc

all: $(NAME)

run: all
	@echo "Running $(NAME)\n"
	@./$(NAME)

$(NAME): $(OBJ)
	@make -C ../libft
	@make -C ../framework
	@$(CC) -o $(NAME_PATH)$(NAME) -L../libft -lft -L../framework -lunit $(INC) $(OBJ)
	@echo "\033[32m$(NAME) created successfully\033[0m"

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2>/dev/null || true
	@make clean -C ../libft
	@make clean -C ../framework

fclean: clean
	@rm -f $(NAME_PATH)$(NAME)
	@rmdir $(NAME_PATH) 2>/dev/null || true
	@make fclean -C ../libft
	@make fclean -C ../framework


re: fclean all

.NOTPARALLEL: re
.PHONY: all clean fclean re run
