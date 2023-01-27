# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 13:04:18 by aahlyel           #+#    #+#              #
#    Updated: 2023/01/27 18:19:07 by aahlyel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------------------------------------------#
#					Colors					#
#-------------------------------------------#

HRED = '\e[1;91m'
HGRN = '\e[1;92m'
HBLU = '\e[1;94m'
NC   = '\e[0m'


OBJS =	obj/pipex.o obj/utils.o obj/parsing.o obj/executer.o obj/ft_split_garbg.o\

CC = cc
RM = rm -rf
mkdir = mkdir -p
CFLAGS = -Wall -Wextra -Werror
dir = obj bin
NAME = bin/pipex
libft = lib/libft
LIBA = lib/libft/bin/libft.a

all : ${NAME}

${NAME} : ${dir} ${OBJS}
	make -C ${libft}
	${CC} ${CFLAGS} ${OBJS} ${LIBA} -o ${NAME}
	printf ${HGRN}"Executable $(NAME) ready ✔️"${NC}

${dir} :
	${mkdir} ${dir}

obj/%.o : src/%.c include/pipex.h
	@printf ${HBLU}"[%-30s] 🕝 \r"${NC} "Compiling ${notdir $@}"
	@${CC} ${CFLAGS} -c -o $@ $<

obj/%.o : src/utils/%.c include/pipex.h
	@printf ${HBLU}"[%-30s] 🕝 \r"${NC} "Compiling ${notdir $@}"
	@${CC} ${CFLAGS} -c -o $@ $<

clean :
	make clean -C ${libft}
	${RM} obj
	printf ${HRED}"Object files removed successfully 🗑️ \n"$(NC)

fclean : clean
	make fclean -C ${libft}
	${RM} bin
	printf ${HRED}"Executables and Archives removed successfully 🗑️\n"$(NC)

re : fclean all

.PHONY : fclean clean compile re
.SILENT : fclean clean re all ${NAME} ${dir}
