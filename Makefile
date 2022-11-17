# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 12:02:12 by jmanet            #+#    #+#              #
#    Updated: 2022/11/17 18:29:20 by jmanet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRCS = srcs/main.c srcs/cmds_utils.c srcs/error_utils.c

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
