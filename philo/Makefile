# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 18:38:31 by kahmada           #+#    #+#              #
#    Updated: 2024/09/25 14:26:38 by kahmada          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   = philo
HEADER = philo.h
CC     = cc
CFLAGS = -Wall -Werror -Wextra
RM     = rm -f

SRC = philo.c\
	  ft_utils.c\
	  parcing.c\
	  rotine.c\
	  filo_func.c\
	  tools_mutex.c\
	  func_for_norm.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)
	