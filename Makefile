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

SRCDIR = src
INCDIR = include
OBJDIR = obj

OBJ_DIRS = $(shell find $(SRCDIR) -type d | sed 's/src/obj/')

CC = gcc
CCFLAGS = -I$(INCDIR) -Wall -Wextra #-Werror

NAME = ft_select
SRC_FILES = main.c

SRC = $(addprefix $(SRCDIR)/,$(SRC_FILES))
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
INCLUDE = $(addprefix $(INCDIR), fractol.h)

all: prebuild $(NAME)

bonus: all

prebuild:
	@for subdir in $(OBJ_DIRS); do mkdir -p $$subdir; done

$(NAME): $(OBJ)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
