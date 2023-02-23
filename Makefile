# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 13:04:18 by aahlyel           #+#    #+#              #
#    Updated: 2023/02/06 20:24:01 by aahlyel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------------------------------------------#
#					Colors					#
#-------------------------------------------#

HRED = '\e[1;91m'
HGRN = '\e[1;92m'
HBLU = '\e[1;94m'
NC   = '\e[0m'


#-------------------------------------------#
#			Mandatory Variables				#
#-------------------------------------------#

SRC =	obj/pipex obj/utils obj/parsing obj/executer obj/ft_split_garbg obj/checking

OBJS =	${addsuffix .o, ${SRC}}

dir = bin obj

libft = lib/libft

LIBA = lib/libft/bin/libft.a

NAME = bin/pipex

#-----------------------------------------------#
#				Bonus Variables					#
#-----------------------------------------------#

BONUS_OBJS = ${addsuffix _bonus.o, ${addprefix bonus/, ${SRC}}}

bonus_dir = ${addprefix bonus/, ${dir}}

bonus_libft = ${addprefix bonus/, ${libft}}

BONUS_LIBA = ${addprefix bonus/, ${LIBA}}

BONUS_NAME =${addprefix bonus/, ${NAME}}

GNLA = bonus/lib/get_next_line/bin/get_next_line.a

GNL = bonus/lib/get_next_line

#-----------------------------------------------#
#				tools Variables					#
#-----------------------------------------------#

CC = cc

RM = rm -rf

mkdir = mkdir -p

CFLAGS =  -fsanitize=address
#-Wall -Wextra -Werror 

#---------------------------------------#
#				Executable				#
#---------------------------------------#

all : $(NAME)

${NAME} : ${dir} $(OBJS)
	make -C ${libft}
	${CC} ${CFLAGS} ${LIBA} ${OBJS} -o ${NAME}
	printf ${HGRN}"Executable $(NAME) ready ✔️"${NC}

obj/%.o : src/%.c include/pipex.h
	@printf ${HBLU}"[%-30s] 🕝 \r"${NC} "Compiling ${notdir $@}"
	@${CC} ${CFLAGS} -c -o $@ $<

obj/%.o : src/utils/%.c include/pipex.h
	@printf ${HBLU}"[%-30s] 🕝 \r"${NC} "Compiling ${notdir $@}"
	@${CC} ${CFLAGS} -c -o $@ $<

${dir} :
	${mkdir} ${dir}
	
#---------------------------------------------------#
#						Bonus						#
#---------------------------------------------------#

bonus : ${BONUS_NAME}

${BONUS_NAME} : ${bonus_dir} ${BONUS_OBJS}
	make -C ${bonus_libft}
	make -C ${GNL}
	${CC} ${CFLAGS} ${BONUS_OBJS} ${GNLA} ${BONUS_LIBA} -o ${BONUS_NAME}
	printf ${HGRN}"Executable $(BONUS_NAME) ready ✔️"${NC}


bonus/obj/%.o : bonus/src/%.c bonus/include/pipex_bonus.h
	@printf ${HBLU}"[%-30s] 🕝 \r"${NC} "Compiling ${notdir $@}"
	@${CC} ${CFLAGS} -c -o $@ $<

bonus/obj/%.o : bonus/src/utils/%.c bonus/include/pipex_bonus.h
	@printf ${HBLU}"[%-30s] 🕝 \r"${NC} "Compiling ${notdir $@}"
	@${CC} ${CFLAGS} -c -o $@ $<

${bonus_dir} :
	${mkdir} ${bonus_dir}

#-----------------------------------------------#
#					Cleaning					#
#-----------------------------------------------#

clean :
	make clean -C ${libft}
	make clean -C ${bonus_libft}
	make clean -C ${GNL}
	${RM} obj bonus/obj
	printf ${HRED}"Object files removed successfully 🗑️ \n"$(NC)

fclean : clean
	make fclean -C ${libft}
	make fclean -C ${bonus_libft}
	make fclean -C ${GNL}
	${RM} bin bonus/bin pipex
	printf ${HRED}"Executables and Archives removed successfully 🗑️\n"$(NC)

re : fclean all

.PHONY : fclean clean re bonus
.SILENT : fclean clean re all bonus ${NAME} ${dir} ${BONUS_NAME} ${bonus_dir} 
