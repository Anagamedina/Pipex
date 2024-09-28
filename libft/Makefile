# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/20 18:38:08 by anamedin          #+#    #+#              #
#    Updated: 2024/09/28 13:00:19 by anamedin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
ARC = ar -rcs

NAME = libft.a
HEADER = libft.h

SRCS =  ft_bzero.c ft_calloc.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_memchr.c\
	ft_atoi.c ft_strchr.c ft_strjoin.c \
    ft_strlen.c ft_strnstr.c ft_substr.c \
    ft_itoa.c ft_strdup.c ft_strlcat.c \
    ft_strmapi.c ft_strrchr.c ft_tolower.c \
    ft_split.c ft_striteri.c ft_strlcpy.c \
    ft_strncmp.c ft_strtrim.c ft_toupper.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_isalnum.c ft_isalpha.c ft_isascii.c \
    ft_isdigit.c ft_isprint.c \
	get_next_line.c get_next_line_utils.c \
	ft_printf.c ft_hex.c ft_print_string.c ft_putchar.c ft_putnbr.c \
	ft_unsignedint.c

SRC_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c\
			ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c\
			ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRC_BONUS:.c=.o)

#Regla implícita
all: $(NAME)

$(NAME): $(OBJS)
	$(ARC) $(NAME) $(OBJS)

bonus: $(OBJS) $(OBJS_BONUS)
		$(ARC) $(NAME) $(OBJS) $(OBJS_BONUS) 


%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

rebonus: fclean bonus

.PHONY: all, clean, fclean, re all bonus
