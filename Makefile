# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 14:22:58 by ltressen          #+#    #+#              #
#    Updated: 2023/05/02 14:50:51 by ltressen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Werror -Wextra

LIBS = -lX11 -lXext -lm
INCLUDE = minilibx-linux/libmlx.a
NAME = fdf.a

EXEC= fdf
SRC = main.c \
	parsing.c
	
OBJ = ${SRC:.c=.o} 
	
all: $(NAME)

$(NAME): ${OBJ}
	make -C libft/
	mv libft/libft.a ${NAME}
	gcc -c ${FLAGS} ${SRC} ${LIBS}
	ar rc ${NAME} ${OBJ}
	gcc ${FLAGS} -g ${SRC} ${NAME} ${INCLUDE} ${LIBS} -o ${EXEC}
	
clean:
	make clean -C libft/
	rm -f ${OBJ}

fclean:
	make clean -C libft/
	rm -f ${OBJ}
	rm -f ${NAME} ${EXEC}

re: fclean all
