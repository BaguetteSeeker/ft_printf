# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epinaud <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 16:30:14 by epinaud           #+#    #+#              #
#    Updated: 2024/08/09 01:21:15 by epinaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES = ft_printf.c ft_print_type.c ft_flag_directives.c ft_print_padding.c ft_base_integrity.c ft_check_dup.c

LIBFTDIR = ../libft

LIBFT_NAME = libft.a

OBJ_DIR = .obj

LIBFTPTH = $(LIBFTDIR)/$(LIBFT_NAME)

LIBFILESLOC = $(addprefix $(LIBFTDIR)/, $(FT_FILES))

FT_FILES = ft_strlen.c ft_nbrlen.c ft_nbrblen.c ft_count_digits.c ft_strchr.c ft_itoa_base.c ft_isdigit.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putnbr_base_fd.c ft_check_dup.c

LIB_OBJ = $(FT_FILES:.c=.o)

#LIBOBJPTH = $(addprefix $(OBJ_DIR)/, $(LIBOBJ))
  
OBJ = $(CFILES:.c=.o)

OBJALL = $(CFILES:.c=.o) $(FT_FILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror -ggdb3

NAME = libftprintf.a

all: $(NAME)

$(NAME): $(OBJ) $(LIB_OBJ)
	ar rcs $(NAME) $(OBJ) $(LIB_OBJ)

bonus: $(OBJ) $(LIB_OBJ)
	ar rcs $(NAME) $(OBJ) $(LIB_OBJ)
clean:
	rm -f $(OBJ) $(LIB_OBJ)

fclean:  clean
	rm -f $(NAME) $(LIBFT_NAME)

re: fclean $(NAME)

relib: 
#	make re -s -C $(LIBFTDIR)
#	ar rcs $(NAME) $(OBJALL) $(LIBOBJPTH)
#	mkdir -p $(OBJ_DIR)
#	ar x --output $(OBJ_DIR) $(FTPATH)

.PHONY:  all clean fclean re bonus
