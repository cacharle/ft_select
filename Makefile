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

LIBFT_DIR = libft

SRCDIR = src
INCDIR = include
OBJDIR = obj

OBJ_DIRS = $(shell find $(SRCDIR) -type d | sed 's/src/obj/')

CC = gcc
CCFLAGS = -I$(LIBFT_DIR)/include -I$(INCDIR) -Wall -Wextra #-Werror
LDFLAGS = -L$(LIBFT_DIR) -lft

NAME = ft_select
SRC_FILES = main.c \
			buf.c \
			state.c \
			stdin.c

SRC = $(addprefix $(SRCDIR)/,$(SRC_FILES))
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
INCLUDE = $(addprefix $(INCDIR), fractol.h)

all: prebuild libft_all $(NAME)

bonus: all

prebuild:
	@for subdir in $(OBJ_DIRS); do mkdir -p $$subdir; done

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean: libft_fclean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

libft_all:
	$(MAKE) -C $(LIBFT_DIR) all

libft_fclean:
	$(MAKE) -C $(LIBFT_DIR) fclean
