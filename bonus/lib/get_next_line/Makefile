# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 06:12:21 by aahlyel           #+#    #+#              #
#    Updated: 2023/01/24 06:12:22 by aahlyel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------
#	Colors
#------------------------------------------

HBLU = '\e[1;94m'
NC   = '\e[0m'

#------------------------------------------
#		 Variables
#------------------------------------------

SRC =	get_next_line_utils.c\
		get_next_line.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

dir = bin obj

AR = ar -rcs

INCLUDE = include/get_next_line.h

NAME = bin/get_next_line.a

#------------------------------------------
#	Substitution of objs
#------------------------------------------

OBJS_a = ${SRC:.c=.o}
OBJS = $(addprefix obj/, $(OBJS_a))
dir = bin obj

#------------------------------------------
#	Archive
#------------------------------------------

all : $(NAME)

${NAME} : ${dir} $(OBJS)
	${AR} ${NAME} ${OBJS}

obj/%.o : src/%.c ${INCLUDE}
	@printf ${HBLU}"[%-30s] 🕝 \r"$(NC) "Compiling $(notdir $@)"
	@ ${CC} ${CFLAGS} -c $< -o $@

${dir} :
	@mkdir -p ${dir}

clean :
	${RM} obj

fclean : clean
	${RM} bin

.PHONY : fclean clean re dir

.SILENT : fclean clean re ${NAME} dir
