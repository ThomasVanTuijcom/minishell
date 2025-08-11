# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 11:08:43 by tvan-tui          #+#    #+#              #
#    Updated: 2025/08/11 18:59:16 by tvan-tui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I ./includes -I ./libft

SRCS_DIR = src
OBJS_DIR = obj

SRCS = \
	$(SRCS_DIR)/builtin/builtin.c \
	$(SRCS_DIR)/builtin/ft_cd.c \
	$(SRCS_DIR)/builtin/ft_cd_update.c \
	$(SRCS_DIR)/builtin/ft_cd_paths.c \
	$(SRCS_DIR)/builtin/ft_echo.c \
	$(SRCS_DIR)/builtin/ft_env.c \
	$(SRCS_DIR)/builtin/ft_exit.c \
	$(SRCS_DIR)/builtin/ft_export.c \
	$(SRCS_DIR)/builtin/ft_export_utils.c \
	$(SRCS_DIR)/builtin/ft_export_replace.c \
	$(SRCS_DIR)/builtin/ft_export_assign.c \
	$(SRCS_DIR)/builtin/ft_pwd.c \
	$(SRCS_DIR)/builtin/ft_unset.c \
	$(SRCS_DIR)/env/create_env.c \
	$(SRCS_DIR)/env/create_exp.c \
	$(SRCS_DIR)/env/search_envp.c \
	$(SRCS_DIR)/env/set_env.c \
	$(SRCS_DIR)/env/utils_env.c \
	$(SRCS_DIR)/error/errors.c \
	$(SRCS_DIR)/error/error_cd.c \
	$(SRCS_DIR)/error/error_syntax.c \
	$(SRCS_DIR)/exec/assign_cmd_options.c \
	$(SRCS_DIR)/exec/build_args_count.c \
	$(SRCS_DIR)/exec/build_cmd_path.c \
	$(SRCS_DIR)/exec/close_exec.c \
	$(SRCS_DIR)/exec/create_files.c \
	$(SRCS_DIR)/exec/duplicating.c \
	$(SRCS_DIR)/exec/execute_cmd.c \
	$(SRCS_DIR)/exec/execute_minishell.c \
	$(SRCS_DIR)/exec/execute_node.c \
	$(SRCS_DIR)/exec/expand_heredoc_lines.c \
	$(SRCS_DIR)/exec/fill_heredoc.c \
	$(SRCS_DIR)/exec/handle_heredoc_variables.c \
	$(SRCS_DIR)/exec/handle_redirections.c \
	$(SRCS_DIR)/exec/heredoc.c \
	$(SRCS_DIR)/exec/init_exec.c \
	$(SRCS_DIR)/exec/is_direct_path_cmd.c \
	$(SRCS_DIR)/exec/path.c \
	$(SRCS_DIR)/exec/read_heredoc.c \
	$(SRCS_DIR)/exec/resolve_cmd_path.c \
	$(SRCS_DIR)/exec/setup_cmd_redirections.c \
	$(SRCS_DIR)/exec/setup_first_command.c \
	$(SRCS_DIR)/exec/setup_io_redirections.c \
	$(SRCS_DIR)/exec/setup_mid_command.c \
	$(SRCS_DIR)/free/free.c \
	$(SRCS_DIR)/free/free_data.c \
	$(SRCS_DIR)/free/free_list.c \
	$(SRCS_DIR)/init/init.c \
	$(SRCS_DIR)/lexer/assign_argument_types.c \
	$(SRCS_DIR)/lexer/assign_command_roles.c \
	$(SRCS_DIR)/lexer/init_lexer.c \
	$(SRCS_DIR)/lexer/utils_lexer.c \
	$(SRCS_DIR)/list/env_list.c \
	$(SRCS_DIR)/list/parse_list.c \
	$(SRCS_DIR)/list/simple_list.c \
	$(SRCS_DIR)/list/utils_list.c \
	$(SRCS_DIR)/parser/add_content.c \
	$(SRCS_DIR)/parser/expand_from_env.c \
	$(SRCS_DIR)/parser/expand_parser_content.c \
	$(SRCS_DIR)/parser/extract_var.c \
	$(SRCS_DIR)/parser/init_parser.c \
	$(SRCS_DIR)/parser/mask_quoted_metachars.c \
	$(SRCS_DIR)/parser/parse_and_expand_dollars.c \
	$(SRCS_DIR)/parser/parse_quote_content.c \
	$(SRCS_DIR)/parser/parse_word.c \
	$(SRCS_DIR)/parser/unclosed_quotes.c \
	$(SRCS_DIR)/parser/utils_parser.c \
	$(SRCS_DIR)/signals/sig_handlers.c \
	$(SRCS_DIR)/signals/sig_setup.c \
	$(SRCS_DIR)/utils/quotes_count.c \
	$(SRCS_DIR)/utils/split_charset.c \
	$(SRCS_DIR)/utils/string_quotes.c \
	$(SRCS_DIR)/utils/utils_char_check.c \
	$(SRCS_DIR)/utils/utils_helper.c \
	$(SRCS_DIR)/utils/utils_number.c \
	$(SRCS_DIR)/utils/utils.c \
	$(SRCS_DIR)/utils/print_structure.c \
	$(SRCS_DIR)/utils/remake_envp.c \
	$(SRCS_DIR)/main.c

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME) -lreadline

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
