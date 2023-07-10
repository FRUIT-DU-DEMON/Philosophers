# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 00:44:43 by hlabouit          #+#    #+#              #
#    Updated: 2023/07/10 01:23:40 by hlabouit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 	philo
SRCS =	$(addprefix parsing/, check_input.c parsing.c) \
		$(addprefix useful_functions/, useful_functions1.c useful_functions2.c useful_functions3.c) \
		lightweight_memory.c philo.c
		
OBJS = $(SRCS:.c=.o)
CC =  cc
CFLAGS = -Werror -Wall -Wextra 

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re