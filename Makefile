# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besellem <besellem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 14:48:05 by besellem          #+#    #+#              #
#    Updated: 2022/05/03 14:45:22 by besellem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION

CC			:= gcc
CFLAGS 		:= -Wall -Wextra -Werror #-g3 -fsanitize=address #-Wpedantic -O2
INCS		:= ./incs/ft_nm.h
IFLAGS 		:= -I./incs -I./libft/incs
LIBFLAGS 	:= -L./libft -lft

# DIRECTORIES

BUILD		:= .build
LIB_DIR		:= libft
SRC_DIR		:= srcs
SUB_DIR		:= elf_utils \
			   elf64
OBJ_DIR 	:= $(BUILD)/obj
DIRS		:= $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SUB_DIR))

# FILES

NAME	:= ft_nm
SRC		:= main.c
SUB_SRC	:= utils.c \
		   sorting.c
SRC		+= $(addprefix elf_utils/, $(SUB_SRC))
SUB_SRC	:= elf64_exec.c
SRC		+= $(addprefix elf64/, $(SUB_SRC))


OBJ 	:= $(SRC:%.c=$(OBJ_DIR)/%.o)

# COLORS

DEFAULT_COLOR	= \033[0m
BLACK_COLOR		= \033[1;30m
RED_COLOR		= \033[1;31m
GREEN_COLOR		= \033[1;32m
YELLOW_COLOR	= \033[1;33m
BLUE_COLOR		= \033[1;34m
MAGENTA_COLOR 	= \033[1;35m
CYAN_COLOR 		= \033[1;36m
WHITE_COLOR 	= \033[1;107m

# MAKEFILE

$(NAME): $(OBJ)
	@echo "Compiling $(RED_COLOR)Libft $(DEFAULT_COLOR)..."
	@$(MAKE) -C $(LIB_DIR) >/dev/null
	@echo "Creating $(RED_COLOR) $@ $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAGS) $(IFLAGS) $^ -o $@ $(LIBFLAGS)
	@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$@ $(BLUE_COLOR)done$(DEFAULT_COLOR)"

all: $(NAME)

bonus: all

clean:
	@echo "Deleting $(CYAN_COLOR)libft $(DEFAULT_COLOR)objs ..."
	@$(MAKE) clean -C $(LIB_DIR) >/dev/null
	@echo "Deleting $(CYAN_COLOR)$(NAME) $(DEFAULT_COLOR)objs ..."
	@rm -rf $(BUILD)

fclean: clean
	@echo "Deleting $(CYAN_COLOR)libft $(DEFAULT_COLOR)library ..."
	@$(MAKE) fclean -C $(LIB_DIR) >/dev/null
	@echo "Deleting $(CYAN_COLOR)$(NAME) $(DEFAULT_COLOR)binary ..."
	@rm -rf $(NAME)
	@rm -rf $(NAME).dSYM

re: fclean all

$(BUILD):
	@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
	@mkdir $@ $(DIRS)
	
$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c $(INCS) | $(BUILD)
	@echo "Compiling $(YELLOW_COLOR)$< $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

.PHONY: all bonus clean fclean