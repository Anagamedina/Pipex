# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 14:26:38 by anamedin          #+#    #+#              #
#    Updated: 2024/09/28 11:28:42 by anamedin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
#----------------------------------------
RM = rm -rf
HEADER_DIR = includes
HEADER = $(HEADER_DIR)/pipex.h
SRC_DIR  = src
#----------------------------------------
SRCS:= $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:.c=.o)
#----------------------------------------
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
#----------------------------------------
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -c $< -o $@
#---------------------------------------
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: all

.PHONY: all clean fclean re
