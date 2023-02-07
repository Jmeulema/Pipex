# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/16 17:42:28 by jmeulema          #+#    #+#              #
#    Updated: 2023/02/07 15:47:23 by jmeulema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

RM = rm -rf
CC = gcc -g
FLAGS = -Wall -Wextra -Werror

INC = \
			pipex.h \

INCS = $(addprefix -I, $(INC))
			
SRCS = \
			SRC/free.c \
			SRC/main.c \
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
