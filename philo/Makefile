# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 17:55:57 by vnafissi          #+#    #+#              #
#    Updated: 2022/03/30 18:35:16 by vnafissi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#*********** VARIABLES ************

#VARIABLE=VALUE
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread
#-fsanitize=thread -g

#-Wconversion
# -fsanitize=thread -fsanitize=undefined

NAME = philo
SRCS = philo.c ft_bzero.c ft_calloc.c ft_atol.c init_variables.c routine_actions.c check_args.c calc_time.c ft_actions.c ft_exit.c ft_utils.c
# parse_input.c parse_input2.c init_mlx.c handle_moves.c handle_exit.c
OBJS=$(SRCS:.c=.o)

#*********** RULES ************
%.o : %.c
	$(CC) ${CFLAGS} ${INCS} -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	${CC} -g ${CFLAGS} -o ${NAME} ${OBJS} ${INCS}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f $(NAME)

re: fclean all

#in case files exist with same name as targets
.PHONY: all clean fclean re bonus
