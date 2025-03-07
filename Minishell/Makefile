# Find the operating system
UNAME := $(shell uname)

# Name of the executable for mandatory part
NAME = minishell

# Name of the executable for bonus part
BONUS = minishell_bonus

# Directories for mandatory part
SRC_DIR = mandatory/src
UTILS_DIR = mandatory/utils
INC_DIR = mandatory/include
OBJ_DIR = obj/mandatory

# Directories for bonus part
BONUS_SRC_DIR = bonus/src
BONUS_UTILS_DIR = bonus/utils
BONUS_INC_DIR = bonus/include
BONUS_OBJ_DIR = obj/bonus

# Directories for common part
LIBFT_DIR = libft
DCLST_DIR = dclst

# Main file for mandatory part
MAIN = $(SRC_DIR)/main.c

# Main file for bonus part
BONUS_MAIN = $(BONUS_SRC_DIR)/main.c

# Sources files for mandatory part	$(SRC_DIR)/iso.c
SRC = \
	$(DCLST_DIR)/dclst1.c \
	$(DCLST_DIR)/dclst2.c \
	$(DCLST_DIR)/dclst3.c \
	$(SRC_DIR)/builtins/cd.c \
	$(SRC_DIR)/builtins/echo.c \
	$(SRC_DIR)/builtins/env.c \
	$(SRC_DIR)/builtins/exit.c \
	$(SRC_DIR)/builtins/export.c \
	$(SRC_DIR)/builtins/pwd.c \
	$(SRC_DIR)/builtins/unset.c \
	$(SRC_DIR)/env/read_env.c \
	$(SRC_DIR)/env/write_env.c \
	$(SRC_DIR)/executor/cmd_execve.c \
	$(SRC_DIR)/executor/exec_cmd.c \
	$(SRC_DIR)/executor/exec_leaf.c \
	$(SRC_DIR)/executor/exec_tree.c \
	$(SRC_DIR)/executor/extract_args.c \
	$(SRC_DIR)/operators/parenthesis.c \
	$(SRC_DIR)/operators/pipe.c \
	$(SRC_DIR)/operators/redirection_in.c \
	$(SRC_DIR)/operators/redirection_out.c \
	$(SRC_DIR)/operators/heredoc_read.c \
	$(SRC_DIR)/operators/heredoc.c \
	$(SRC_DIR)/parser/binary_tree.c \
	$(SRC_DIR)/parser/check_synthax.c \
	$(SRC_DIR)/parser/get_token1.c \
	$(SRC_DIR)/parser/get_token2.c \
	$(SRC_DIR)/parser/lexer.c \
	$(SRC_DIR)/signals/signal_handler.c \
	$(SRC_DIR)/text_transformer/dollar_manager.c \
	$(SRC_DIR)/text_transformer/filenames_extraction.c \
	$(SRC_DIR)/text_transformer/filenames_searcher.c \
	$(SRC_DIR)/text_transformer/get_files_in_dir.c \
	$(SRC_DIR)/text_transformer/wildcard_manager.c \
	$(UTILS_DIR)/delete_functions.c \
	$(UTILS_DIR)/error_messages.c \
	$(UTILS_DIR)/ft_strtol.c \
	$(UTILS_DIR)/initialize_minishell.c \
	$(UTILS_DIR)/node_token_info1.c \
	$(UTILS_DIR)/node_token_info2.c \
	$(UTILS_DIR)/node_token_info3.c \
	$(UTILS_DIR)/token_error_message.c \
	$(UTILS_DIR)/utils_functions.c \
	mandatory/test/tests_to_remove.c \
	$(MAIN)

# Sources files for bonus part
BONUS_SRC =	\
	$(BONUS_MAIN)

# Objects files for mandatory part
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Objects files for bonus part
BONUS_OBJ = $(BONUS_SRC:$(BONUS_SRC_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)

# Compilation options (for Linux and MacOS)
ifeq ($(UNAME), Linux)
	CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)/headers
	LDFLAGS = -lreadline -L$(LIBFT_DIR) -lft_inc
else ifeq ($(UNAME), Darwin)
	CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)/headers -I/opt/homebrew/opt/readline/include
	LDFLAGS = -L$(LIBFT_DIR) -lft_inc -L/opt/homebrew/opt/readline/lib -lreadline
else
	$(error Unsupported OS)
endif

# Compiler
CC = gcc

# Rule to compile the mandatory part
all: $(NAME)
$(NAME): $(OBJ) $(LIBFT_DIR)/libft_inc.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

# Rule to compile the bonus part
bonus: $(BONUS)
$(BONUS): $(BONUS_OBJ) $(LIBFT_DIR)/libft_inc.a
	$(CC) $(CFLAGS) -o $(BONUS) $^ $(LDFLAGS)

# Rule to compile libft
$(LIBFT_DIR)/libft_inc.a:
	$(MAKE) -C $(LIBFT_DIR)

# Rules to compile the objects files of the mandatory part
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Rules to compile the objects files of the bonus part
$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
$(BONUS_OBJ_DIR)/%.o: $(BONUS_UTILS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_UTILS_DIR)/%.c
	@mkdir -p $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean the objects files
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf obj

# Rule to clean the objects files and the executables
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(NAME) $(BONUS)

# Rule to recompile the project
re: fclean all

# Phony rule
.PHONY: all clean fclean re bonus