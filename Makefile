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

CFLAGS = -Wall -Wextra -Werror -g3 -libreadline -I$(HEADER)

HEADER = minishell

SRCS =	main.c\
		parsing/tokenizer/tokenizer.c\
		parsing/tokenizer/token_utils.c\
		parsing/tokenizer/token_init.c\

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

all: $(Name)

$(Name): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(Name)

re: fclean all

.PHONY: all clean fclean re