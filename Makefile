# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 13:04:18 by aahlyel           #+#    #+#              #
#    Updated: 2023/01/04 13:04:19 by aahlyel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS =	pipex.o\
		libft/ft_memset.o\
		libft/ft_bzero.o\
		libft/ft_calloc.o\
		libft/ft_memcpy.o\
		libft/ft_strdup.o\
		libft/ft_strlen.o\
		libft/ft_substr.o\
		libft/ft_split.o\
		libft/ft_strjoin.o\
		libft/ft_strnstr.o\
		libft/ft_substr.o\

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex.a
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
