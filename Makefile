PROGRAMS := servidor cliente
SOURCES := open62541 function
CC := gcc
#FLAGS := -Wall -Werror -pedantic -Wextra -fno-stack-protector -std=c99 -DUA_ARCHITECTURE_POSIX
#FLAGS := -Wall -pedantic -Wextra -fno-stack-protector -std=c99 -DUA_ARCHITECTURE_POSIX
FLAGS := -fno-stack-protector -std=c99 -DUA_ARCHITECTURE_POSIX

all: $(SOURCES) $(PROGRAMS) rmobj

open62541: open62541.h open62541.c
	$(CC) $(FLAGS) -c open62541.c

function: function.h function.c
	$(CC) $(FLAGS) -c function.c

servidor: servidor.c function.o open62541.o
	$(CC) $(FLAGS) servidor.c open62541.o function.o -o servidor

cliente: cliente.c function.o open62541.o
	$(CC) $(FLAGS) cliente.c open62541.o function.o -o cliente

rmobj:
	rm -rf *.o

clean: 
	rm -rf cliente servidor
