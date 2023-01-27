# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/16 17:42:28 by jmeulema          #+#    #+#              #
#    Updated: 2023/01/27 12:00:59 by jmeulema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

RM = rm -rf
CC = gcc -g3
FLAGS = -Wall -Wextra -Werror

INC = \
			pipex.h \

INCS = $(addprefix -I, $(INC))
			
SRCS = \
			SRC/free.c \
			SRC/main.c \
			SRC/pipex.c \
			SRC/pipex_utils.c \
			SRC/split_path.c \
			SRC/utils.c \
			
OBJS = ${SRCS:.c=.o}

all : ${NAME}

$(NAME) : $(OBJS)
		@$(CC) $(FLAGS) -o $(NAME) $(OBJS)

clean :
		${RM} ${OBJS}

fclean : clean 
		${RM} ${NAME}

re : fclean all

%.o: %.c
		${CC} ${FLAGS} -o $@ -c $<
