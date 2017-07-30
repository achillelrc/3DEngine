##
## Makefile for Wolf
## 
## Made by Laroche Achille
## Login   <binary@epitech.net>
## 
## Started on  Sat Jun 10 14:58:48 2017 Laroche Achille
## Last update Sun Jul 30 19:01:12 2017 Laroche Achille
##

CC =	gcc -g3

RM =	rm -rf

CPPFLAGS += -I./include

NAME =	wolf3d

LIB = -lc_graph_prog -lm

SRC =	src/main.c	\
	src/lib.c	\
	src/scan.c	\
	src/init.c	\
	src/gnl.c
#	src/wolf.c	\
#	src/scan.c	\
#	src/init.c	\
#	src/lib.c	\
#	src/init.c	\
#	src/calc.c	\
#	src/basics.c

OBJS =	$(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) $(LIB) -o $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

mr_clean :
	find -type f -name "*~" -delete -o -type f -name "#*#" -delete

re : fclean all

.PHONY : all clean fclean mr_clean re
