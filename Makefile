# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 13:26:33 by swilliam          #+#    #+#              #
#    Updated: 2022/10/06 18:02:07 by swilliam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Source files
FILLER_DIR = ./sources/
FILLER_FILES = main.c read_input.c heatmap.c piece_placement.c initialise.c

# Libft
LIBFT_DIR = ./libft/
LIBFT = libft.a


# Object files
OBJ_DIR = ./objects/
OBJ = $(addprefix $(OBJ_DIR), $(FILLER_FILES:.c=.o))

# Compilation
CC = gcc
FLAGS = -Wall -Wextra -Werror
DEBUG = -g
INCLUDES = -I./includes -I$(LIBFT_DIR)includes -I./eval_tests
ADD_LIB = -L. $(LIBFT)
FILLER = swilliam.filler

# Utilities
DELETE = $(FILLER) $(OBJ) filler.trace log ./eval_tests/filler.trace
PLAYER = ./eval_tests/play.py

all:		$(FILLER)

$(FILLER): $(OBJ) $(OBJ_DIR)
			@make all -C $(LIBFT_DIR)
			@printf "\r                                       \r"
			@$(CC) $(FLAGS) $(INCLUDES) $(OBJ) $(LIBFT_DIR)$(LIBFT) -o $(FILLER)
			@printf "\r                                       \r"
			@printf "\rExecutable ($(FILLER)) created.\n"

$(OBJ_DIR)%.o: $(FILLER_DIR)%.c
			@mkdir -p $(OBJ_DIR)
			@printf "\rCompiling objects..."
			@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
			@printf "\r                                       \r"

clean:
			@printf "\rCleaning objects..."
			@make clean -sC $(LIBFT_DIR)
			@rm -f $(OBJ)
			@rm -rf $(OBJ_DIR)
			@printf "\r                                       \r"
			@printf "\rObjects cleaned.\n"

fclean: 	clean
			@printf "\rCleaning all created files..."
			@make fclean -sC $(LIBFT_DIR)
			@rm -f $(DELETE)
			@printf "\r                                       \r"
			@printf "\rAll created files removed.\n"

play:		$(FILLER)
			python $(PLAYER)

re:			fclean all

.PHONY: all clean fclean re play