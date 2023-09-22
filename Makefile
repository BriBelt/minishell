# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 12:14:19 by jaimmart          #+#    #+#              #
#    Updated: 2023/09/22 18:49:22 by bbeltran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
EXTRAFLAGS = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
# EXTRAFLAGS = -L/usr/lib/x86_64-linux-gnu -lreadline
RM = rm -rf

LIBFT_A = libft.a
LIBF_DIR = libft/
LIBFT  = $(addprefix $(LIBF_DIR), $(LIBFT_A))

HEADER = minishell.h struct.h

MINI_SRC = path_utils.c pwd.c builtins.c cd.c quote_utils.c echo.c quotes.c \
env.c export.c free_utils.c list_utils.c minishell.c \
redirections.c t_basic.c typesort.c typesort_utils.c unset.c pipes.c \
new_parsing.c node_join.c quote_split.c space_split.c var_expand.c heredoc.c exe_redirect.c \
t_red.c execution.c execution_utils.c t_command.c env_sort.c children.c children_utils.c \
exit.c signals.c var_expand_utils.c export_utils.c heredoc_utils.c
MINI_OBJ = $(MINI_SRC:.c=.o)


$(NAME):	$(MINI_OBJ)
				@echo  "     - Making libft..."
				@make -C $(LIBF_DIR)
				@${CC} ${FLAGS} ${MINI_OBJ} ${EXTRAFLAGS} ${LIBFT} -o ${NAME}
				@echo "$(NAME) created."

$(MINI_OBJ): 	$(MINI_SRC)
				@echo  "     - Making object files..."
				@$(CC) $(FLAGS) -c $(MINI_SRC)

all:		$(NAME)

clean:
			@$(RM) $(MINI_OBJ)
			@make -C $(LIBF_DIR) clean
			@echo "object files removed."

fclean:	clean
			@$(RM) $(NAME)
			@make -C $(LIBF_DIR) fclean
			@echo "everything removed."

re:		fclean all

.PHONY:		all clean fclean re
