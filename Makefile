# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 13:26:33 by swilliam          #+#    #+#              #
#    Updated: 2022/10/04 15:54:33 by swilliam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Source files
FILLER_FILES = main.c read_input.c heatmap.c piece_placement.c initialise.c

# Directories
LIBFT_DIR = ./libft/
LIBFT_SRC = ./libft/sources/
FILLER_DIR = ./sources/

# Objects
OBJ_DIR = ./objects/
LIBFT_OBJ = $(addprefix $(OBJ_DIR), $(LIBFT_FILES:.c=.o))
FTP_OBJ = $(addprefix $(OBJ_DIR), $(FILLER_FILES:.c=.o))
OBJ = $(LIBFT_OBJ) $(FTP_OBJ)

# Compilation
NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes -I$(LIBFT_DIR)includes -I./eval_tests
ADD_LIB = -L. $(NAME)
EXECUTABLE = swilliam.filler
LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): 	libft $(OBJ)

$(OBJ_DIR)%.o: $(FILLER_DIR)%.c
			@mkdir -p $(OBJ_DIR)
			@printf "\rCompiling objects..."
			@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
			@printf "\r                                       \r"

libft:
			@make all -C $(LIBFT_DIR)

clean:
			@printf "\rCleaning objects..."
			@make clean -sC $(LIBFT_DIR)
			@rm -f $(OBJ)
			@rm -rf $(OBJ_DIR)
			@printf "\r                                       \r"
			@printf "\rObjects cleaned.\n"

fclean: 	clean
			@printf "\rCleaning library and executable..."
			@make fclean -sC $(LIBFT_DIR)
			@rm -f $(EXECUTABLE)
			@rm -f filler.trace
			@printf "\r                                       \r"
			@printf "\rLibrary and executable removed.\n"

test:		all
			gcc $(INCLUDES) $(OBJ) $(LIBFT_DIR)$(NAME) -o $(EXECUTABLE)

vm:			test
			./resources/filler_vm -p1 ./swilliam.filler -p2 ./resources/players/carli.filler -f ./resources/maps/map01

re:			fclean all

.PHONY: all clean fclean re test vm libft