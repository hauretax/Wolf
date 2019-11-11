# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/01 10:51:52 by hutricot          #+#    #+#              #
#    Updated: 2019/11/11 18:03:00 by hutricot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=wolf3d

CC = gcc
CCF = -fsanitize=address
ML=-lmlx -framework OpenGL -framework AppKit
FLAGS = -Wall -Wextra
INCLUDES = -I$(HEADERS_DIR)

HEADERS_LIST = wolf.h
HEADERS_DIR = ./include/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRC_LIST = main.c			\
			do_a_map.c		\
			key.c			\
			raycasting.c	\
			mooving.c

SRC_DIR = ./src/
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

YELLOW = \033[033m
GREEN = \033[032m
BLUE = \033[36m
RED = \033[031m
PURPLE = \033[35m
RESET = \033[0m

all: $(NAME)

$(NAME):$(OBJ_DIR) $(OBJ)
	@echo "$(PURPLE)Sources compilation $(RESET)[$(GREEN)OK$(RESET)]\n"
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJ) -o $(NAME) $(ML)
	@echo "[$(BLUE)$(NAME) Compiled$(RESET)]"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "\n$(BLUE)Obj directory...$(RESET)[$(GREEN)created$(RESET)]\n"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(YELLOW)$(notdir $(basename $@))...$(RESET)[$(GREEN)OK$(RESET)]"


clean:
	@rm -rf $(OBJ_DIR)
	@echo "\n$(RED)Obj directory...$(RESET)[$(PURPLE)deleted$(RESET)]\n"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME)...$(RESET)[$(PURPLE)deleted$(RESET)]\n"

sani :$(OBJ_DIR) $(OBJ)
	@echo "$(YELLOW)Sources compilation $(RESET)[$(GREEN)OK$(RESET)]\n"
	@$(CC) $(CCF) $(FLAGS) $(INCLUDES) $(OBJ) -o $(NAME)
	@echo "[$(BLUE)$(NAME) Compiled$(RESET)]"

re: fclean all

.PHONY: all clean fclean re sani
