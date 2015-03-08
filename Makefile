NAME = asyncdext
LIBNAME = lib$(NAME).so
ARCHIVE = lib$(NAME).a

INC = -I ../include
LIBS = -levent -levent_openssl -lonig -lqlibc -lasyncd

all:
	cd build/ ;\
	gcc $(INC) -c -Wall -Werror -fpic ../src/router.c ;\
	gcc -shared -o libasyncdext.so router.o
