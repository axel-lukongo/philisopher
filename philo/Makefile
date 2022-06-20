# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 21:47:44 by alukongo          #+#    #+#              #
#    Updated: 2022/06/20 16:04:25 by alukongo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc 

RM = rm -rf

NAME = philo

MANDATORY = philo.c\
			time.c\
			utils.c\
			init.c\
			free.c\
			main.c\
			death.c\
			action.c\
			parsing.c\

MANDATORY_SRCS	=	${MANDATORY}

BONUS_SRCS	=	${BONUS}

MANDATORY_OBJS	= ${MANDATORY_SRCS:.c=.o}

CFLAGS	= -g -Wall -Werror -Wextra #-fsanitize=thread

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${MANDATORY_OBJS}
		${CC} ${CFLAGS}   -o ${NAME} ${MANDATORY_OBJS} -lpthread


clean:
	${RM} ${MANDATORY_OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
