# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 13:04:18 by aahlyel           #+#    #+#              #
#    Updated: 2023/01/17 00:15:16 by aahlyel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS =	pipex.o\
		utils.o\
		foramtter.o\
		executer.o\
		ft_split_garbg.o\
		libft/ft_memset.o\
		libft/ft_bzero.o\
		libft/ft_calloc.o\
		libft/ft_memcpy.o\
		libft/ft_strdup.o\
		libft/ft_strlen.o\
		libft/ft_substr.o\
		libft/ft_strjoin.o\
		libft/ft_strnstr.o\
		libft/ft_substr.o\
		libft/ft_putendl_fd.o\
		libft/ft_lstadd_back.o\
		libft/ft_lstclear.o\
		libft/ft_lstnew.o\
		libft/ft_lstdelone.o\
		libft/ft_lstlast.o\

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
AR = ar -rcs

all : ${NAME} compile

${NAME} : ${OBJS}
	${AR} ${NAME} $^

compile :
	${CC} ${CFLAGS} -o pipex ${NAME}

%.o : %.c pipex.h
	${CC} ${CFLAGS} -c -o $@ $<

clean :
	${RM} ${OBJS}

fclean : clean
	${RM} ${NAME} pipex

re : fclean all

.PHONY : fclean clean compile re
