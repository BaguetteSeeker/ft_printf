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

LIBFTPTH = $(LIBFTDIR)/$(LIBFT_NAME)
  
OBJ = $(CFILES:.c=.o)

LIBOBJ = ft_isalpha.c ft_isdigit.c ft_strlcat.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_atoi_base.c ft_itoa_base.c

OBJALL = $(CFILES:.c=.o) $(BONUS:.c=.o) $(LIBOBJ:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I .

#LDFLAGS = -L../libft

#LDLIBS = -lft

#LDLIBS += $(LDFLAGS)

NAME = libftprintf.a

OBJ_PATH = .obj

all: $(NAME)

$(NAME): $(OBJALL)
	make -s -C $(LIBFTDIR)
	cp $(LIBFTPTH) $(LIBFT_NAME)
	ar rcs $(NAME) $(OBJALL)
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
	mkdir -p $(OBJ_PATH)
	ar x --output $(OBJ_PATH) $(FTPATH)

.PHONY:  all clean fclean re bonus
