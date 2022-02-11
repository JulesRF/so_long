# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 16:58:24 by jroux-fo          #+#    #+#              #
#    Updated: 2022/02/10 20:10:36 by jroux-fo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRCS_FILES	=	main.c 					\
				ft_itoa.c				\
				ft_utils.c				\
				ft_switch.c				\
				ft_square.c				\
				ft_checkmap.c			\
				ft_alloc_map.c			\
				ft_checkchar.c			\
				ft_enemy_move.c			\
				get_next_line.c			\
				ft_checkrectangle.c		\
				get_next_line_utils.c	\

FLAGS = -Wall -Werror -Wextra# -g3 -fsanitize=address

INCLUDES = header

PATH = srcs

OBJ_DIR = obj

OBJ = $(addprefix $(OBJ_DIR)/,$(SRCS_FILES:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: $(PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf "Compiling $< ...\n"
	@gcc $(FLAGS) -I $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	@gcc $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@printf "Executable $@ created !\n"

clean:
	@printf "Deleting objects\n"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "Deleting executable\n"
	@rm -rf $(NAME)

re: fclean all

.PHONY:		all clean fclean re