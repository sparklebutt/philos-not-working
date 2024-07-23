#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/11 15:26:56 by araveala          #+#    #+#              #
#    Updated: 2024/07/19 14:43:46 by araveala         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

#-fsanitize=address
NAME = philo
CFLAGS = -Wall -Wextra -Werror -g  $(HEADERS)
CFILES = main.c free_things.c utils.c user_input.c init_data.c
OFILES = $(CFILES:.c=.o)
HEADERS = -I philo.h

all: $(NAME)

$(NAME): $(OFILES)
	@cc $(OFILES) $(HEADERS) $(CFLAGS) -o $(NAME)
clean:
	@rm -rf $(OFILES)
fclean: clean
	@rm -f $(NAME)
re: fclean all

PHONY: all clean fclean re
