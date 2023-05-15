# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/14 17:40:26 by arabenst          #+#    #+#              #
#    Updated: 2023/05/15 11:50:21 by arabenst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	atfatMaps

EXE			=	$(NAME)
ARCHIVE		=	$(NAME).a

SRCDIR		=	./src
OBJDIR		=	./obj
LIBDIR		=	./lib

EXE_SRC		=	$(SRCDIR)/main.c
EXE_OBJ		=	$(addprefix $(OBJDIR)/,$(notdir $(EXE_SRC:.c=.o)))

LIB_SRCS	=	$(filter-out $(EXE_SRC),$(wildcard $(SRCDIR)/*.c))
LIB_OBJS	=	$(addprefix $(OBJDIR)/,$(notdir $(LIB_SRCS:.c=.o)))

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

AR			=	ar
ARFLAGS		=	rcs

RM			=	rm
RMFLAGS		=	-Rf

LIBFT_DIR	=	$(LIBDIR)/libft
LIBFT_LIB	=	libft.a
LIBFT		=	$(LIBFT_DIR)/$(LIBFT_LIB)

$(EXE): $(ARCHIVE) $(EXE_OBJ)
	$(CC) -o $@ $^

$(ARCHIVE): $(LIB_OBJS) | $(LIBFT)
	cp $(LIBFT) $(ARCHIVE)
	$(AR) $(ARFLAGS) $@ $^

$(LIBFT): $(LIBDIR)
	git clone https://github.com/aaron-22766/libft.git $(LIBFT_DIR); make -C $(LIBFT_DIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

all: $(EXE)

clean:
	$(RM) $(RMFLAGS) $(OBJDIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(RMFLAGS) $(EXE) $(ARCHIVE)
	make -C $(LIBFT_DIR) fclean

libclean:
	$(RM) $(RMFLAGS) $(LIBDIR)

flibclean: fclean libclean

re: fclean all

exe: $(EXE)

archive: $(ARCHIVE)

.PHONY: all clean fclean libclean flibclean re
