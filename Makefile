# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epinaud <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 16:30:14 by epinaud           #+#    #+#              #
#    Updated: 2024/06/14 19:34:19 by epinaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SFILES = ft_printf.c

BONUS = 
  
OFILES = $(SFILES:.c=.o)

OFILESALL = $(SFILES:.c=.o) $(BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I .

NAME = libftprint.a

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)
bonus: $(OFILESALL)
	ar rcs $(NAME) $(OFILESALL)
clean:
	rm -f $(OFILESALL)

fclean:  clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:  all clean fclean re bonus
