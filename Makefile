# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbranco- <jbranco-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 15:04:25 by jbranco-          #+#    #+#              #
#    Updated: 2023/06/05 14:39:53 by jbranco-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c src/utils.c src/struct_init.c src/routine.c src/printing.c
OBJS = $(SRC:.c=.o)
CFLAGS =  -Wall -Wextra -Werror -fPIE -fsanitize=address -pthread

NAME = philo

all: $(NAME)

$(NAME): $(OBJS) 
	cc $(CFLAGS) $(OBJS) -o $(NAME) 

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME) 

re: clean all
