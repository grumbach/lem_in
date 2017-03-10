# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/11 00:03:30 by agrumbac          #+#    #+#              #
#    Updated: 2017/03/11 00:24:51 by agrumbac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC = lem_in.c

OBJDIR = objs

CFLAGS = -Wall -Wextra -Werror

DEP = lem_in.h libft/includes/libft.h libft/includes/ft_printf.h

CC = gcc

OBJ = $(addprefix ${OBJDIR}/, $(SRC:.c=.o))

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

all: ${NAME}
	@echo ${G}Success"   "[${NAME}]${X}

${NAME}: ${OBJ}
	make -C libft/
	echo ${B}Compiling [${NAME}]...${X}
	${CC} ${CFLAGS} -I./libft/includes/ -Llibft/ -lft -I. -o $@ ${OBJ}

${OBJDIR}/%.o : ./srcs/%.c ${DEP}
	@echo ${Y}Compiling [$@]...${X}
	@/bin/mkdir -p ${OBJDIR}
	@${CC} ${CFLAGS} -I./libft/includes/ -I. -c -o $@ $<
	@printf ${UP}${CUT}

clean:
	echo ${R}Cleaning"  "[libft objs]...${X}
	make -C libft/ clean
	echo ${R}Cleaning"  "[objs]...${X}
	/bin/rm -Rf ${OBJDIR}

fclean: clean
	make -C libft/ fclean
	echo ${R}Cleaning"  "[${NAME}]...${X}
	/bin/rm -f ${NAME} test

test:
	${CC} -I./libft/includes/ -fsanitize=address -Llibft/ -lft -I. -o ${NAME} \
	$(addprefix srcs/, ${SRC})

re: fclean all

build: ${OBJ}

.PHONY: all clean fclean re test panic build
.SILENT: ${NAME} ${OBJDIR} clean fclean test
