CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f 

NAME = philo
HEADER = philo.h

SRCS =	init.c			\
		main.c  		\
		philo.c 		\
		utils.c			\
		function_time.c	\

SRCS_OBJS = ${SRCS:%.c=%.o}

all: ${NAME}

${NAME}:${SRCS_OBJS}
	${CC} ${CFLAGS} $^ -o ${NAME}

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(SRCS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
