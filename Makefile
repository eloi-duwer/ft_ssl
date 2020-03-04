# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/31 13:12:01 by eduwer            #+#    #+#              #
#    Updated: 2020/03/04 15:20:35 by eduwer           ###   ########.fr        #
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

CC = gcc

CFLAGS = -I./include -g -I./libft/include -Wall -Wextra

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
