# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/11 00:03:30 by agrumbac          #+#    #+#              #
#    Updated: 2017/03/09 12:38:13 by agrumbac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC = lem_in.c

OBJDIR = objs

CFLAGS = -Wall -Wextra -Werror

CC = gcc

OBJ = $(addprefix ${OBJDIR}/, $(SRC:.c=.o))

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
W = "\033[34;1m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

all: ${NAME}

panic:
	@echo ${W}"DON'T PANIC"${X}

${NAME}: panic ${OBJ}
	@make -C libft/
	@${CC} ${CFLAGS} -I./libft/includes/ -Llibft/ -lft -I. -o $@ ${OBJ}
	@echo ${B}Compiling [${NAME}]...${X}
	@echo ${G}Success"   "[${NAME}]${X}

${OBJDIR}/%.o : ./srcs/%.c
	@echo ${UP}${CUT}${Y}Compiling [$@]...${X}
	@/bin/mkdir -p ${OBJDIR}
	@${CC} ${CFLAGS} -I./libft/includes/ -I. -c -o $@ $<

clean:
	@echo ${R}Cleaning"  "[libft objs]...${X}
	@make -C libft/ clean
	@echo ${R}Cleaning"  "[objs]...${X}
	@/bin/rm -Rf ${OBJDIR}

fclean: clean
	@make -C libft/ fclean
	@echo ${R}Cleaning"  "[${NAME}]...${X}
	@/bin/rm -f ${NAME} test

test:
	@${CC} -I./libft/includes/ -fsanitize=address -Llibft/ -lft -I. -o ${NAME} \
	$(addprefix srcs/, ${SRC})

re: fclean all

build: panic ${OBJ}

.PHONY: all clean fclean re test panic build
