# Resuelva la parte a.- en el archivo parte-a.c.
# Compile con:
#     $ make test-parte-a
# Pruebe con:
#     $ ./test-parte-a
#
# Resuelva parte b.- en el archivo parte-b.c
# Compile con:
#     $ make test-parte-b
# Pruebe con:
#     $ ./test-parte-b
#
# Resuelva parte c.- en los archivo serv.c y cliente.c.
# Compile con:
#     $ make serv cliente
# Pruebe manualmente con el ejemplo del enunciado.  Necesitara 4 ventanas:
# una para el servidor y 3 para los clientes.
#

CFLAGS= -g -std=c99 -Wall -pedantic
LDFLAGS= -g
LDLIBS= -lpthread -lm

all: test-parte-a test-parte-b serv cliente

test-parte-a.o parte-a.o: integral.h

test-parte-a: test-parte-a.o parte-a.o

test-parte-b.o parte-b.o fun.o: integral.h

test-parte-b: test-parte-b.o parte-a.o parte-b.o fun.o util.o

cliente.o serv.o libjsocket.o: integral.h util.h jsocket.h

cliente: cliente.o parte-a.o parte-b.o fun.o util.o libjsocket.o

serv: serv.o util.o libjsocket.o

clean:
	rm -f *.o
	rm -f test-parte-a test-parte-b cliente serv
