# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 16:15:27 by keteo             #+#    #+#              #
#    Updated: 2025/07/24 16:15:27 by keteo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
Name = minishell

SRCS_DIR = parsing/tokenizer
OBJ_DIR = objs

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3


SRCS =	main.c\
		parsing/tokenizer.c\
		parsing/token_utils.c\
		parsing/general_utils.c\
# 		parsing/parser.c\
# 		parsing/parser_utils.c\


OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

LIBFT = libft/libft.a

$(LIBFT) :
	@make -C libft

all: $(Name)

$(Name): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(Name)

re: fclean all

.PHONY: all clean fclean re