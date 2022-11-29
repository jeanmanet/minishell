# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 12:02:12 by jmanet            #+#    #+#              #
#    Updated: 2022/11/19 09:05:59 by jmanet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRCS = $(wildcard srcs/*.c)

INCLUDES = includes/minishell.h

CC = gcc

FLAGS = -Wall -Werror -Wextra

LIBS = libraries/libft.a -lreadline

.c.o:
	${CC} -I ${INCLUDES} ${FLAGS} -c $< -o ${<:.c=.o}

OBJS = ${SRCS:.c=.o}

all : ${NAME}

${NAME} : ${OBJS} ${INCLUDES}
	${CC} ${SRCS} ${LIBS} -I includes/ ${FLAGS} -o ${NAME}

clean :
	rm -rf ${OBJS}

fclean : clean
	rm -rf ${NAME}

re : fclean all

d :
	${CC} ${SRCS} ${LIBS} -I includes/ -o ${NAME} -g

