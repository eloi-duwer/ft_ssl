# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/31 13:12:01 by eduwer            #+#    #+#              #
#    Updated: 2021/01/28 22:45:22 by eduwer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME = main.c \
	helpers.c \
	process.c \
	md5/md5.c \
	md5/digest.c \
	md5/rounds.c \
	sha256/sha256.c \
	sha256/sha256_helpers.c \
	sha512/sha512.c \
	sha512/sha512_helpers.c \
	sha384/sha384.c

NAME = ft_ssl

CC = clang

CFLAGS = -I./include -g -I./libft/include -Wall -Wextra -Werror

SRCF = ./srcs/

OBJF = ./obj/

OBJS = $(addprefix $(OBJF), $(SRC_NAME:.c=.o))

LFT = libft/libft.a

all: $(NAME)

$(NAME): $(LFT) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -g -L./libft -lft

$(LFT):
	make -C ./libft

$(OBJF)%.o: $(SRCF)%.c
	@mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) -c $(addprefix $(SRCF), $*.c)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
