# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epinaud <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 16:30:14 by epinaud           #+#    #+#              #
#    Updated: 2024/06/18 16:39:11 by epinaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES = ft_printf.c

LIBFTDIR = ../libft

LIBFT_NAME = libft.a

OBJ_DIR = .obj

LIBFTPTH = $(LIBFTDIR)/$(LIBFT_NAME)

LIBOBJLOC = $(addprefix $(LIBFTDIR)/, $(LIBOBJ))

LIBC = $(LIBOBJLOC:.o=.c)

LIBOBJ = ft_strlen.o ft_nbrlen.o ft_tolower.o ft_toupper.o ft_atoi.o ft_strdup.o ft_itoa.o ft_atoi_base.o ft_itoa_base.o ft_putstr_fd.o ft_putchar_fd.o ft_putnbr_fd.o

LIBOBJPTH = $(addprefix $(OBJ_DIR)/, $(LIBOBJ))
  
OBJ = $(CFILES:.c=.o)

OBJALL = $(CFILES:.c=.o) $(BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -ggdb3

NAME = libftprintf.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBOBJLOC)
	cp $(LIBOBJLOC) $(LIBC) .
	ar rcs $(NAME) $(OBJ) $(LIBOBJLOC)

clean:
	rm -f $(OBJ) $(LIBOBJ)

fclean:  clean
	rm -f $(NAME)

re: fclean $(NAME)

relib: 
	make re -s -C $(LIBFTDIR)
	ar rcs $(NAME) $(OBJALL) $(LIBOBJPTH)
#	mkdir -p $(OBJ_DIR)
#	ar x --output $(OBJ_DIR) $(FTPATH)

.PHONY:  all clean fclean re bonus
