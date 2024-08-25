# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epinaud <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 16:30:14 by epinaud           #+#    #+#              #
#    Updated: 2024/08/25 16:11:42 by epinaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SFILES = ft_printf.c \
		ft_print_argument.c \
		ft_parse_directives.c \
		ft_print_directives.c \
		ft_base_integrity.c \
		ft_check_dup.c \

FT_FILES = 	ft_strlen.c \
			ft_nbrlen.c \
			ft_nbrblen.c \
			ft_count_digits.c \
			ft_strchr.c \
			ft_isdigit.c \
			ft_putchar_fd.c \
			ft_itoa_base.c \
			ft_putstr_fd.c \
			ft_putnbr_fd.c \
			ft_putnbr_base_fd.c \

OBJ_DIR = .obj

PRINTF_OBJ = $(SFILES:.c=.o)

LIB_OBJ = $(FT_FILES:.c=.o)

OBJALL = $(SFILES:.c=.o) $(FT_FILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror -ggdb3

NAME = libftprintf.a

LIBFT_NAME = libft.a

all: $(NAME)

$(NAME): $(PRINTF_OBJ) $(LIB_OBJ)
	ar rcs $(NAME) $(PRINTF_OBJ) $(LIB_OBJ)

bonus: $(PRINTF_OBJ) $(LIB_OBJ)
	ar rcs $(NAME) $(PRINTF_OBJ) $(LIB_OBJ)
clean:
	rm -f $(PRINTF_OBJ) $(LIB_OBJ)

fclean:  clean
	rm -f $(NAME) $(LIBFT_NAME)

re: fclean $(NAME)

.PHONY:  all clean fclean re bonus
