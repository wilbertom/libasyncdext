NAME = asyncdext
LIBNAME = lib$(NAME).so
ARCHIVE = lib$(NAME).a

FILES = ../src/router.c
INC = -I ../include

LIBS = -levent -levent_openssl -lonig -lqlibc -lasyncd

all:
	cd build/ ;\
	gcc $(INC) -c -Wall -Werror -fpic  $(FILES) ;\
	gcc -shared -o $(LIBNAME) router.o
