# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/04 12:49:13 by hdelaby           #+#    #+#              #
#    Updated: 2017/03/07 13:19:26 by hdelaby          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libunit.a
CC = gcc
AR = ar -rcs
CFLAGS = -Wall -Wextra -Werror
INC = -I./includes

SRC_PATH = ./src/
SRC_NAME = run_unit_test.c \
		   load_test.c \
		   launch_tests.c

OBJ_PATH = ./obj/
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "\033[32m$(NAME) created successfully\033[0m"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
