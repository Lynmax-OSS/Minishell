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
NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =	main.c \
		parsing/tokenizer.c \
		parsing/token_parser.c \
		parsing/general_utils_func.c \
		parsing/extractor_func.c \
		parsing/syntax_validator.c\
		parsing/init_env.c\
		parsing/expand_var.c\
		parsing/token_assigner.c\
		parsing/cmd_list_init.c\
		parsing/expand_tokens.c\
		execution/1_execution.c\
		execution/1a_exec_utils.c\
		execution/2_pipes.c\
		execution/2a_pipe_setup.c\
		execution/2b_pipe_setup_fork.c\
		execution/2c_pipe_utils.c\
		execution/3_wait_children.c\
		execution/4_redirection.c\
		execution/4a_single_redir.c\
		execution/4b_heredoc.c\
		execution/4c_expand.c\
		execution/5_builtin.c\
		execution/5a_echo.c\
		execution/5b_pwd.c\
		execution/5c_env.c\
		execution/5d_exit.c\
		execution/5e_cd.c\
		execution/5f_unset.c\
		execution/5g_export.c\
		execution/5g1_print_sorted.c\
		execution/5g2_update_env.c\
		execution/6_run_external.c\
		execution/6a_env_convert.c\
		execution/6b_exec_clean.c\
		execution/6c_external_utils.c\
		execution/7_signals.c\

OBJ_DIR = objs
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

