# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nifromon <nifromon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 05:37:45 by nifromon          #+#    #+#              #
#    Updated: 2025/01/24 05:56:58 by nifromon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name
NAME_ALL =			libft_inc.a
NAME_LIBFT =		libft.a
NAME_FT_PRINTF =	ft_printf.a
NAME_GNL =			get_next_line.a

# Arguments
CC = 				gcc
CFLAGS = 			-Wall -Wextra -Werror

# Repositories
# Sources
SRCS_DIR =			src
LIBFT_SRC =			$(SRCS_DIR)/libft_SRC
FT_PRINTF_SRC = 	$(SRCS_DIR)/ft_printf_SRC
GNL_SRC =			$(SRCS_DIR)/get_next_line_SRC
# Headers
HEADERS_DIR =		headers
LIBFT_H =			$(HEADERS_DIR)/libft_H/
FT_PRINTF_H =		$(HEADERS_DIR)/ft_printf_H/
GNL_H =				$(HEADERS_DIR)/get_next_line_H/
OBJS_DIR =			obj

# Utils
AR =				ar -rcs
RM =				rm -rf

# Sources and Objects
LIBFT_SRCS = 		\
					$(LIBFT_SRC)/ft_isalpha.c $(LIBFT_SRC)/ft_isdigit.c \
					$(LIBFT_SRC)/ft_isalnum.c $(LIBFT_SRC)/ft_isascii.c \
					$(LIBFT_SRC)/ft_isprint.c $(LIBFT_SRC)/ft_strlen.c \
					$(LIBFT_SRC)/ft_memset.c $(LIBFT_SRC)/ft_bzero.c \
					$(LIBFT_SRC)/ft_memcpy.c $(LIBFT_SRC)/ft_memmove.c \
					$(LIBFT_SRC)/ft_strlcpy.c $(LIBFT_SRC)/ft_strlcat.c \
					$(LIBFT_SRC)/ft_toupper.c $(LIBFT_SRC)/ft_tolower.c \
					$(LIBFT_SRC)/ft_strchr.c $(LIBFT_SRC)/ft_strrchr.c \
					$(LIBFT_SRC)/ft_strncmp.c $(LIBFT_SRC)/ft_memchr.c \
					$(LIBFT_SRC)/ft_memcmp.c $(LIBFT_SRC)/ft_strnstr.c \
					$(LIBFT_SRC)/ft_atoi.c $(LIBFT_SRC)/ft_calloc.c \
					$(LIBFT_SRC)/ft_strdup.c $(LIBFT_SRC)/ft_substr.c \
					$(LIBFT_SRC)/ft_strjoin.c $(LIBFT_SRC)/ft_strtrim.c \
					$(LIBFT_SRC)/ft_split.c $(LIBFT_SRC)/ft_itoa.c \
					$(LIBFT_SRC)/ft_strmapi.c $(LIBFT_SRC)/ft_striteri.c \
					$(LIBFT_SRC)/ft_putchar_fd.c $(LIBFT_SRC)/ft_putstr_fd.c \
					$(LIBFT_SRC)/ft_putendl_fd.c $(LIBFT_SRC)/ft_putnbr_fd.c \
					$(LIBFT_SRC)/ft_lstnew.c $(LIBFT_SRC)/ft_lstadd_front.c \
					$(LIBFT_SRC)/ft_lstsize.c $(LIBFT_SRC)/ft_lstlast.c \
					$(LIBFT_SRC)/ft_lstadd_back.c $(LIBFT_SRC)/ft_lstdelone.c \
					$(LIBFT_SRC)/ft_lstclear.c $(LIBFT_SRC)/ft_lstiter.c \
					$(LIBFT_SRC)/ft_lstmap.c

LIBFT_OBJS = 		$(LIBFT_SRCS:$(LIBFT_SRC)/%.c=$(OBJS_DIR)/$(LIBFT_SRC)/%.o)
					
FT_PRINTF_SRCS =	\
					$(FT_PRINTF_SRC)/ft_printf.c $(FT_PRINTF_SRC)/ftpf_init.c \
					$(FT_PRINTF_SRC)/ftpf_format_c.c $(FT_PRINTF_SRC)/ftpf_check.c \
					$(FT_PRINTF_SRC)/ftpf_format_d.c \
					$(FT_PRINTF_SRC)/ftpf_format_i.c \
					$(FT_PRINTF_SRC)/ftpf_format_p.c \
					$(FT_PRINTF_SRC)/ftpf_format_s.c \
					$(FT_PRINTF_SRC)/ftpf_format_u.c \
					$(FT_PRINTF_SRC)/ftpf_format_x_low.c \
					$(FT_PRINTF_SRC)/ftpf_format_x_upp.c

FT_PRINTF_OBJS = 	$(FT_PRINTF_SRCS:$(FT_PRINTF_SRC)/%.c=$(OBJS_DIR)/$(FT_PRINTF_SRC)/%.o)
					
GNL_SRCS =			\
					$(GNL_SRC)/get_next_line.c \
					$(GNL_SRC)/get_next_line_utils.c

GNL_OBJS = 			$(GNL_SRCS:$(GNL_SRC)/%.c=$(OBJS_DIR)/$(GNL_SRC)/%.o)

# Rules and Dependencies
all: 				$(NAME_ALL)

$(NAME_ALL):		$(LIBFT_OBJS) $(FT_PRINTF_OBJS) $(GNL_OBJS)
					$(AR) $(NAME_ALL) $(LIBFT_OBJS) $(FT_PRINTF_OBJS) $(GNL_OBJS)

libft:				$(NAME_LIBFT)

$(NAME_LIBFT):		$(LIBFT_OBJS)
					$(AR) $(NAME_LIBFT) $(LIBFT_OBJS)

$(OBJS_DIR)/$(LIBFT_SRC)/%.o: $(LIBFT_SRC)/%.c
					@mkdir -p $(dir $@)
					$(CC) -c $(CFLAGS) -I $(LIBFT_H) $< -o $@

clean_libft:
					$(RM) $(OBJS_DIR)/$(LIBFT_SRC)
					
fclean_libft: 		clean_libft
					$(RM) $(NAME_LIBFT)

re_libft: 				fclean_libft libft

ft_printf:			$(NAME_FT_PRINTF) libft

$(NAME_FT_PRINTF):	$(FT_PRINTF_OBJS)
					$(AR) $(NAME_FT_PRINTF) $(FT_PRINTF_OBJS)

$(OBJS_DIR)/$(FT_PRINTF_SRC)/%.o: $(FT_PRINTF_SRC)/%.c
					@mkdir -p $(dir $@)
					$(CC) -c $(CFLAGS) -I $(FT_PRINTF_H) $< -o $@

clean_ft_printf:
					$(RM) $(OBJS_DIR)/$(FT_PRINTF_SRC)
					
fclean_ft_printf: 	clean_ft_printf
					$(RM) $(NAME_FT_PRINTF)

re_ft_printf: 		fclean_ft_printf ft_printf

get_next_line:		$(NAME_GNL)

$(NAME_GNL):		$(GNL_OBJS)
					$(AR) $(NAME_GNL) $(GNL_OBJS)

$(OBJS_DIR)/$(GNL_SRC)/%.o: $(GNL_SRC)/%.c
					@mkdir -p $(dir $@)
					$(CC) -c $(CFLAGS) -I $(GNL_H) $< -o $@

clean_gnl:
					$(RM) $(OBJS_DIR)/$(GNL_SRC)
					
fclean_gnl: 		clean_gnl
					$(RM) $(NAME_GNL)

re_gnl: 			fclean_gnl get_next_line

clean:				clean_libft clean_ft_printf clean_gnl
					$(RM) $(OBJS_DIR)

fclean: 			clean fclean_libft fclean_ft_printf fclean_gnl
					$(RM) $(NAME_ALL)

re: 				fclean all

.PHONY: 			all libft ft_printf get_next_line clean fclean re \
					clean_libft clean_ft_printf clean \
					fclean_libft fclean_ft_printf fclean_gnl \
					re_libft re_ft_printf re_gnl

#END
