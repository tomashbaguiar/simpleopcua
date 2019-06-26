PROGRAMS := servidor cliente
#SOURCES := open62541 function
SOURCES := open62541
CC := gcc
#FLAGS := -Wall -Werror -pedantic -Wextra -fno-stack-protector -std=c99 -DUA_ARCHITECTURE_POSIX
#FLAGS := -Wall -pedantic -Wextra -fno-stack-protector -std=c99 -DUA_ARCHITECTURE_POSIX
FLAGS := -fno-stack-protector -std=c99 -DUA_ARCHITECTURE_POSIX

all: $(SOURCES) $(PROGRAMS) rmobj

open62541: open62541.h open62541.c
	$(CC) $(FLAGS) -c open62541.c

function: function.h function.c
	$(CC) $(FLAGS) -c function.c

#servidor: servidor.c function.o open62541.o
#	$(CC) $(FLAGS) servidor.c open62541.o function.o -o servidor

#servidor: servidor.c function.o
#	$(CC) $(FLAGS) servidor.c function.o -o servidor

#servidor: servidor.c
#	$(CC) $(FLAGS) open62541.c servidor.c -o servidor

servidor: servidor.c open62541.o
	$(CC) $(FLAGS) open62541.o servidor.c -o servidor

#cliente: cliente.c function.o open62541.o
#	$(CC) $(FLAGS) cliente.c open62541.o function.o -o cliente

#cliente: cliente.c function.o
#	$(CC) $(FLAGS) cliente.c function.o -o cliente

#cliente: cliente.c
#	$(CC) $(FLAGS) cliente.c -o cliente

cliente: cliente.c open62541.o
	$(CC) $(FLAGS) cliente.c open62541.o -o cliente

rmobj:
	rm -rf *.o

clean: 
	rm -rf cliente servidor
