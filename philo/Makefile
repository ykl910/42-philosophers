# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyang <kyang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 11:25:43 by kyang             #+#    #+#              #
#    Updated: 2025/01/16 13:15:09 by kyang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

SRC_PATH = src/
SRC		=	utils.c \
			init_data.c \
			dinner_thread.c \
			monitor_thread.c \
			main.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))

CFLAGS = -Wall -Wextra #-Werror 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	
%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -O3 -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re bonus