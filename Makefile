# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/11 00:03:30 by agrumbac          #+#    #+#              #
#    Updated: 2017/03/11 18:06:50 by agrumbac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SEE_NAME = see-ants

SRC = lem_in.c lem_in_parse.c

SEE_SRC = lem_in_viewer.c

OBJDIR = objs

CFLAGS = -Wall -Wextra -Werror

DEP = lem_in.h libft/includes/libft.h libft/includes/ft_printf.h

CC = gcc

OBJ = $(addprefix ${OBJDIR}/, $(SRC:.c=.o))

SEE_OBJ = $(addprefix ${OBJDIR}/, $(SEE_SRC:.c=.o))

MLX = minilibx_macos/

FRAMEWORKS = -framework OpenGL -framework AppKit

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
W = "\033[0m""\033[34;1m"
WR = "\033[0m""\033[31;5m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

all: ant ${NAME} ${SEE_NAME}
	@echo ${G}Success"   "[${NAME}]${X}

${NAME}: ${OBJ}
	@make -C libft/
	@echo ${B}Compiling [${NAME}]...${X}
	@${CC} ${CFLAGS} -Ilibft/includes/ -Llibft/ -lft -I. -o $@ ${OBJ}

${SEE_NAME}: ${SEE_OBJ}
	@echo ${B}Compiling [mlx]...${X}
	@make -C ${MLX}
	@echo ${G}Success"   "[mlx]${X}
	@echo ${B}Compiling [${SEE_NAME}]...${X}
	@${CC} ${CFLAGS} -Ilibft/includes/ -I. -I${MLX} -Llibft/ -lft \
		-L${MLX} -lmlx ${FRAMEWORKS} -o $@ ${SEE_OBJ}

${OBJDIR}/%.o : ./srcs/%.c ${DEP}
	@echo ${Y}Compiling [$@]...${X}
	@/bin/mkdir -p ${OBJDIR}
	@${CC} ${CFLAGS} -Ilibft/includes/ -I. -c -o $@ $<
	@printf ${UP}${CUT}

clean:
	@echo ${R}Cleaning"  "[libft objs]...${X}
	@make -C libft/ clean
	@echo ${R}Cleaning"  "[mlx]...${X}
	@make -C ${MLX} clean
	@echo ${R}Cleaning"  "[objs]...${X}
	@/bin/rm -Rf ${OBJDIR}

fclean: clean
	@make -C libft/ fclean
	@echo ${R}Cleaning"  "[${NAME}]...${X}
	@/bin/rm -f ${NAME}
	@echo ${R}Cleaning"  "[${SEE_NAME}]...${X}
	@/bin/rm -f ${SEE_NAME}

test:
	@${CC} -g -I./libft/includes/ -fsanitize=address -Llibft/ -lft \
	-I. -o ${NAME} $(addprefix srcs/, ${SRC})

ant:
	@echo ${W}
	@echo "              ,"
	@echo "     _,-'\\   /|   .    .    /\`."
	@echo " _,-'     \\_/_|_  |\   |\`. /   \`._,--===--.__"
	@echo "^       _/\"/  \" \ : \__|_ /.  ,'   :.  :. .  \`-._"
	@echo "      "${WR}"//"${W}"  ^ "${WR}"/7"${W}"  t'\"\"    \"\`-._/ ,'\   :   :  :  . \`."
	@echo "      "${WR}"Y"${W}"     "${WR}"L/"${W}"  )\         ]],'   \  :   :  :   :  \`."
	@echo "      |        /  \`.n_n_n,','\_    \ ;   ;  ;   ;   _>"
	@echo "      |__    ,'     |  \\\`-'    \`-.__\_______.==---'"
	@echo "      //  \`\"\"\\      |   \\            \\"
	@echo "     \|     |/      /    \            \\"
	@echo "	           /     |             \`."
	@echo "	          /      |               ^"
	@echo "	         ^       |"
	@echo "                         ^"
	@echo ${X}

re: fclean all

build: ${OBJ}

.PHONY: all clean fclean re test panic build
