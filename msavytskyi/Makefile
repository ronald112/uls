NAME = uls

INC = ./inc/uls.h \
		./libmx/inc/libmx.h \

INCL = ./libmx/inc/libmx.h \

HEADTMP = ./uls.h \
			./libmx.h \
			./libmx/libmx.h

FILES = *

SRC = $(addsuffix .c, $(FILES))

SRCS = $(addprefix src/, $(SRC))

OBJ = $(addsuffix .o, $(FILES))

OBJO = $(addprefix obj/, $(OBJ))

CFLGS = -std=c11 -Wall -Werror -Wpedantic -Wextra

all: install clean

install:
	@make -C libmx -f Makefile install
	@cp $(INC) $(SRCS) .
	@cp $(INCL) ./libmx/
	@clang $(CFLGS) -c  $(SRC) libmx/inc/libmx.h -Iinc
	@mkdir -p obj
	@mv $(OBJ) ./obj
	@clang $(CFLGS) $(OBJO) libmx/libmx.a -o $(NAME)

uninstall:
	@rm $(NAME)

clean:
	@make -C libmx -f Makefile uninstall
	@make -C libmx -f Makefile clean
	@rm -rf $(OBJO) $(SRC) $(HEADTMP)
	@rm -rf ./obj
	@rm -rf ./libmx/libmx.h.gch

reinstall: uninstall all
