NAME = asyncdext
LIBNAME = lib$(NAME).so
ARCHIVE = lib$(NAME).a

FILES = ../src/router.c ../src/route.c ../src/asyncdext.c
INC = -I ../include/

LIBS = -levent -levent_openssl -lqlibc -lasyncd

all:
	cd build/ ;\
	gcc -std=c99 $(INC) -c -Wall -Werror -fpic  $(FILES) ;\
	gcc -shared -o $(LIBNAME) router.o route.o asyncdext.o

install:
	cp build/$(LIBNAME) /usr/local/lib/
	cp -r include/$(NAME) /usr/local/include/$(NAME)

uninstall:
	rm /usr/local/lib/$(LIBNAME)
	rm -rf /usr/local/include/$(NAME)

clean:
	rm -f build/*.o
	rm -f build/*.so
