# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 17:34:56 by aaammari          #+#    #+#              #
#    Updated: 2023/01/31 19:57:27 by aaammari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f 

NAME = philo_m
NAME_BONUS = philo_b

HEADER = ./philo/philo.h
HEADER_BONUS = ./philo_bonus/philo_bonus.h

SRCS =	./philo/init.c			\
		./philo/main.c  		\
		./philo/philo.c 		\
		./philo/utils.c			\
		./philo/function_time.c	\

SRCS_BONUS =	./philo_bonus/init_bonus.c			\
				./philo_bonus/main.c  				\
				./philo_bonus/philo_bonus.c 		\
				./philo_bonus/utils_bonus.c			\
				./philo_bonus/function_time_bonus.c	\
				./philo_bonus/create_processes.c	\


OBJS = ${SRCS:%.c=%.o}
OBJS_BONUS = ${SRCS_BONUS:%.c=%.o}

all: ${NAME}

${NAME}:${OBJS} ${HEADER}
	${CC} ${CFLAGS} $(OBJS) -o ${NAME}

bonus: ${OBJS_BONUS} ${HEADER_BONUS}
	${CC} ${CFLAGS} $(OBJS_BONUS) -o ${NAME_BONUS}

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all bonus

.PHONY: all clean fclean re
