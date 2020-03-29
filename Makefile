# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacharle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/24 09:19:49 by cacharle          #+#    #+#              #
#    Updated: 2020/02/27 13:11:14 by cacharle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE = make
RM = rm -f

NAME = ft_select

LIBFTDIR = libft
SRCDIR = src
INCDIR = include
OBJDIR = obj

OBJSUBDIRS = $(shell find $(SRCDIR) -type d | sed 's/src/obj/')

CC = gcc
CCFLAGS = -I$(LIBFTDIR)/include -I$(INCDIR) -Wall -Wextra #-Werror
LDFLAGS = -L$(LIBFTDIR) -lft -lcurses

SRC = $(shell find $(SRCDIR) -type f -name "*.c")
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
INC = $(shell find $(INCDIR) -type f -name "*.h")

all: prebuild libft_all $(NAME)

bonus: all

prebuild:
	@for subdir in $(OBJSUBDIRS); do mkdir -p $$subdir; done

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC)
	$(CC) $(CCFLAGS) -c -o $@ $<

clean: libft_fclean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

libft_all:
	$(MAKE) -C $(LIBFTDIR) all

libft_fclean:
	$(MAKE) -C $(LIBFTDIR) fclean
