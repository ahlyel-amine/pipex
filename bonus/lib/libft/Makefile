# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 13:21:42 by aahlyel           #+#    #+#              #
#    Updated: 2023/01/27 18:17:40 by aahlyel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC = 	ft_atoi.c\
			ft_bzero.c\
			ft_calloc.c\
			ft_isalnum.c\
			ft_isalpha.c\
			ft_isascii.c\
			ft_isdigit.c\
			ft_isprint.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_memset.c\
			ft_strchr.c\
			ft_strdup.c\
			ft_strlcat.c\
			ft_strlcpy.c\
			ft_strlen.c\
			ft_strncmp.c\
			ft_strnstr.c\
			ft_strrchr.c\
			ft_tolower.c\
			ft_toupper.c\
			ft_substr.c\
			ft_strjoin.c\
			ft_strtrim.c\
			ft_split.c\
			ft_itoa.c\
			ft_strmapi.c\
			ft_striteri.c\
			ft_putchar_fd.c\
			ft_putstr_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c \
			ft_lstnew.c\
			ft_lstadd_front.c\
			ft_lstsize.c\
			ft_lstlast.c\
			ft_lstadd_back.c\
			ft_lstdelone.c\
			ft_lstclear.c\
			ft_lstiter.c\
			ft_lstmap.c

OBJS_PATH = $(addprefix obj/, $(SRC))
OBJS = $(OBJS_PATH:.c=.o)
HBLU = '\e[1;94m'
NC   = '\e[0m'

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

AR = ar -rcs

NAME = bin/libft.a

dir = obj bin

INCLUDE = include/libft.h

all : ${NAME}

${NAME} : ${dir} ${OBJS}
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

.PHONY : fclean clean  dir

.SILENT : fclean clean  ${NAME} dir
