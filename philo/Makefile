# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-kass <ael-kass@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 15:14:51 by ael-kass          #+#    #+#              #
#    Updated: 2021/11/28 19:43:18 by ael-kass         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

FLAGS = -Wall -Wextra -Werror -pthread -g

SRCS = ./ft_atoi.c \
		./tools.c \
		./actions.c \
		./supervisor.c \
		./parsing.c \
		./initialization.c \
		./main.c

INCLUDE = philosophers.h

all : $(NAME)

$(NAME): $(SRCS) $(INCLUDE)
	@$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	@rm -rf *.o
	@rm -rf philo.dSYM
	@rm -rf a.out.dSYM

fclean: clean
	@rm -rf $(NAME)

re: fclean all