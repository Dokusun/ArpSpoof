##
## EPITECH PROJECT, 2018
## nmobjdump
## File description:
## Makefile
##

SRCDIR	=	./Arpspoofing/src

NAME =  myARPspoof

SRC	=	$(wildcard $(SRCDIR)/*.c)

OBJ = $(SRC:.c=.o)

CFLAGS	=	-I./Arpspoofing/Includes/ -W -Wall -Wextra -g

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
