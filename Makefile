# Find the operating system
UNAME := $(shell uname)

# Name of the executable for mandatory part
NAME = minishell

# Directories for bonus part
SRC_DIR = files/bonus/src
UTILS_DIR = files/bonus/utils
INC_DIR = files/bonus/include
OBJ_DIR = obj/bonus

# Directories for common part
LIBFT_DIR = files/libft
DCLST_DIR = files/dclst

# Main file for bonus part
MAIN = $(SRC_DIR)/main.c

# Sources files for bonus part
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
	$(SRC_DIR)/executor/extract_filename.c \
	$(SRC_DIR)/operators/parenthesis.c \
	$(SRC_DIR)/operators/pipe.c \
	$(SRC_DIR)/operators/redirection_in.c \
	$(SRC_DIR)/operators/redirection_out.c \
	$(SRC_DIR)/operators/heredoc_delimiter.c \
	$(SRC_DIR)/operators/heredoc.c \
	$(SRC_DIR)/parser/binary_tree.c \
	$(SRC_DIR)/parser/check_synthax.c \
	$(SRC_DIR)/parser/get_token1.c \
	$(SRC_DIR)/parser/get_token2.c \
	$(SRC_DIR)/parser/lexer.c \
	$(SRC_DIR)/signals/main_signal_handler.c \
	$(SRC_DIR)/text_transformer/dollar_manager.c \
	$(SRC_DIR)/text_transformer/filenames_extraction.c \
	$(SRC_DIR)/text_transformer/filenames_searcher.c \
	$(SRC_DIR)/text_transformer/get_files_in_dir.c \
	$(SRC_DIR)/text_transformer/wildcard_manager.c \
	$(UTILS_DIR)/delete_functions1.c \
	$(UTILS_DIR)/delete_functions2.c \
	$(UTILS_DIR)/error_messages1.c \
	$(UTILS_DIR)/error_messages2.c \
	$(UTILS_DIR)/ft_strtol.c \
	$(UTILS_DIR)/get_next_node.c \
	$(UTILS_DIR)/initialize_minishell.c \
	$(UTILS_DIR)/node_token_info1.c \
	$(UTILS_DIR)/node_token_info2.c \
	$(UTILS_DIR)/node_token_info3.c \
	$(UTILS_DIR)/utils_functions.c \
	$(MAIN)

# Objects files for mandatory part
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compilation options (for Linux and MacOS)
# compilation options to test memory leaks on mac: -fsanitize=undefined -fsanitize=address -g
ifeq ($(UNAME), Linux)
	CFLAGS = -g -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)/headers
	LDFLAGS = -lreadline -L$(LIBFT_DIR) -lft_inc
else ifeq ($(UNAME), Darwin)
	CFLAGS = -fsanitize=undefined -fsanitize=address -g -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)/headers -I/opt/homebrew/opt/readline/include
	LDFLAGS = -L$(LIBFT_DIR) -lft_inc -L/opt/homebrew/opt/readline/lib -lreadline
else
	$(error Unsupported OS)
endif

# Compiler
CC = cc

# Rule to compile the mandatory part
all: $(NAME)
$(NAME): $(OBJ) $(LIBFT_DIR)/libft_inc.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

# Rule to compile the bonus part
bonus: all

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

# Rule to clean the objects files
clean:
	make -C $(LIBFT_DIR) clean
	rm -rf obj

# Rule to clean the objects files and the executables
fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

# Rule to recompile the project
re: fclean all

# Phony rule
.PHONY: all clean fclean re bonus
