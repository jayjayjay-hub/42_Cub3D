# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 11:59:48 by kosnakam          #+#    #+#              #
#    Updated: 2024/09/28 15:52:27 by kosnakam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# project name
NAME			= cub3D

# compiler
CC				= clang

# commands
RM				= rm -rf
NORM			= norminette

# library
LIBFT_NAME		= libft.a
LIBFT_DIR		= libft/

# mlx
MLX_NAME		= libmlx.a
MLX_DIR			= minilibx/

# flags
CFLAGS			= -Wall -Wextra -Werror
LFLAGS			= -L$(MLX_DIR) -lXext -lX11

# include
INCLUDE_DIR		= include/
INCLUDE			= -I$(INCLUDE_DIR)
LIBFT_INCLUDE 	= -I$(LIBFT_DIR)$(INCLUDE_DIR) -I$(MLX_DIR)

# srcs and objs
SRC_DIR			= src/
OBJ_DIR			= .obj/
SRC_FILES		= $(shell find $(SRC_DIR) -name "*.c" | sed "s/.*\///")
OBJ_FILES		= $(SRC_FILES:%.c=%.o)
OBJS			= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

# color ***********************
Y				= "\033[33m"
R				= "\033[31m"
G				= "\033[32m"
B				= "\033[34m"
X				= "\033[0m"
UP				= "\033[A"
CUT				= "\033[K"
# *****************************

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo $(Y) "$(NAME) src files successfully compiled\n" $(X)
	@echo $(B) "--> Into $(LIBFT_DIR)" $(X)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo $(B) "<-- Out of $(LIBFT_DIR)\n" $(X)
	@echo $(B) "$(NAME) creating" $(X)
	@printf $(UP)$(CUT)
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(MLX_DIR)$(MLX_NAME) $(LIBFT_DIR)$(LIBFT_NAME) -o $(NAME)
	@echo $(G) "!! $(NAME) created !!\n" $(X)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo $(Y) "Compiling $<" $(X)
	@$(CC) $(INCLUDE) $(LIBFT_INCLUDE) $(CFLAGS) -c $< -o $@
	@printf $(UP)$(CUT)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ_DIR)
	@echo $(R) "$(OBJ_DIR) has been removed!!" $(X)

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@echo $(R) "$(NAME) $(OBJ_DIR) has been removed!!" $(X)

re: fclean all

leak: CFLAGS += -g
leak: LFLAGS += -fsanitize=address
leak: re

norm:
	@echo $(R) "<<< $(NAME) error count >>>" $(X)
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error | grep -v Error! | wc -l
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error || true

.PHONY: all clean fclean re leak norm
