CC=gcc
CFLAGS = -Wall -g

all: lexer.o
    $(CC) $(CFLAGS) lexer.o -o lexer

lexer.o: lexer.c
    $(CC) $(CFLAGS) -c lexer.c

clean: 
  rm -f *.o  

run:
  ./lexer

 
