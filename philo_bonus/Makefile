# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyang <kyang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 11:25:43 by kyang             #+#    #+#              #
#    Updated: 2025/01/24 18:57:25 by kyang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = cc

INCLUDE_PATH = include_bonus

SRC_PATH = src_bonus/
SRC		=	utils.c \
			init_data.c \
			dinner_process.c \
			monitor_process.c \
			getters_setters.c \
			main.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))

CFLAGS = -Wall -Wextra -Werror 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -pthread -lrt
	
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -O3 -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re bonus