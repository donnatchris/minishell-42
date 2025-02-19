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
	$(SRC_DIR)/builtins/pwd.c \
	$(SRC_DIR)/env/read_env.c \
	$(SRC_DIR)/env/write_env.c \
	$(SRC_DIR)/parser/binary_tree.c \
	$(SRC_DIR)/parser/check_token_list.c \
	$(SRC_DIR)/parser/get_token.c \
	$(SRC_DIR)/parser/parser_main_for_test.c \
	$(SRC_DIR)/parser/tokenizer.c \
	$(UTILS_DIR)/dollar_manager.c \
	$(MAIN)

# Sources files for bonus part
BONUS_SRC =	\
	$(BONUS_MAIN)

# Objects files for mandatory part
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Objects files for bonus part
BONUS_OBJ = $(BONUS_SRC:$(BONUS_SRC_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)

# Compilation options
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)/headers
LDFLAGS = -lreadline -L$(LIBFT_DIR) -lft_inc

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