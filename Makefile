##
## Makefile for program compilation
##

.PHONY: all clean fclean re unit_tests tests_run

NAME	=	navy_battle

SRC		=	src/error.c						\
			src/game.c						\
			src/map.c						\
			src/connection.c				\
			src/my_attack.c					\
			src/enemy_attack.c				\
			src/condition.c					\

LIB		=	lib/lib_putchar.c				\
			lib/lib_putstr.c				\
			lib/lib_putnbr.c				\
			lib/lib_printf.c				\
			lib/lib_strlen.c				\
			lib/lib_strdup.c				\
			lib/lib_nbrlen.c				\
			lib/lib_getnbr.c				\
			lib/lib_strcmp.c				\
			lib/lib_abs.c					\
			lib/lib_arrlen.c				\
			lib/lib_free_arr.c				\
			lib/lib_str_to_word_array.c		\

TEST	=	test/test_main.c				\
			test/test_lib.c					\

OBJ		=	$(SRC:.c=.o) $(LIB:.c=.o)

CC		=	gcc -g

INCLUDE = 	-I ./include

CFLAGS	=	$(INCLUDE) -Werror -Wall -Wextra

all:	$(NAME)

$(NAME): $(OBJ)
		$(CC) -o $(NAME) $(OBJ) main.c

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)
		rm -f *.gcda
		rm -f *.gcno
		rm -f unit_tests

re:		fclean all

unit_tests: fclean all
		$(CC) -o unit_tests $(SRC) $(LIB) $(TEST) \
		$(INCLUDE) --coverage -lcriterion

tests_run: unit_tests
		./unit_tests
		gcovr --exclude test/
