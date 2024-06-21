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

BFILES = 

LIBFTDIR = ../libft

LIBFT_NAME = libft.a

OBJ_DIR = .obj

LIBFTPTH = $(LIBFTDIR)/$(LIBFT_NAME)

LIBOBJ = ft_strlen.o ft_nbrlen.o ft_tolower.o ft_toupper.o ft_atoi.o ft_strdup.o ft_substr.o ft_strjoin.o ft_split.o ft_itoa.o ft_atoi_base.o ft_itoa_base.o ft_putstr_fd.o ft_putchar_fd.o

LIBOBJPTH = $(addprefix $(LIBFTDIR)/$(OBJ_DIR)/, $(LIBOBJ))
  
OBJ = $(CFILES:.c=.o)

OBJALL = $(CFILES:.c=.o) $(BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I. -ggdb3

#LDFLAGS = -L../libft

#LDLIBS = -lft

#LDLIBS += $(LDFLAGS)

NAME = libftprintf.a

all: $(NAME)

$(NAME): $(OBJALL)
	make re -s -C $(LIBFTDIR)
	ar rcs $(NAME) $(OBJALL) $(LIBOBJPTH)
#bonus: $(OBJALL)
#	ar rcs $(NAME) $(OBJALL)
clean:
	rm -f $(OBJALL)

fclean:  clean
	rm -f $(NAME)

re: fclean $(NAME)

libft: 
	echo "bonjour\n"
	make -s -C ../libft
	mkdir -p $(OBJ_DIR)
	ar x --output $(OBJ_DIR) $(FTPATH)

.PHONY:  all clean fclean re bonus
