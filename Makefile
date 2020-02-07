# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/31 13:12:01 by eduwer            #+#    #+#              #
#    Updated: 2020/02/07 14:51:57 by eduwer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME = main.c \
	digest.c \
	rounds.c

NAME = ft_ssl

CC = gcc

CFLAGS = -I./include -g -I./libft/include

SRCF = ./srcs/

OBJF = ./obj/

OBJS = $(addprefix $(OBJF), $(SRC_NAME:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) -o $(NAME) $(OBJS) -g -L./libft -lft

$(OBJF)%.o: $(SRCF)%.c
	@mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) -c $(addprefix $(SRCF), $*.c)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
