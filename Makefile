# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 16:58:24 by jroux-fo          #+#    #+#              #
#    Updated: 2022/01/24 17:19:28 by jroux-fo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRCS_FILES	=	main.c \

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
	@gcc $(FLAGS) -I $(INCLUDES) $(OBJ) -o $(NAME)
	@printf "Executable $@ created !\n"

clean:
	@printf "Deleting objects\n"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "Deleting executable\n"
	@rm -rf $(NAME)

re: fclean all

.PHONY:		all clean fclean re