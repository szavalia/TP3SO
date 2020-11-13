all: server
	gcc client.c -o client

clean:
	rm *.o client our_server

server: asm
	gcc our_server.c runme.o -o our_server -lm

asm:
	nasm -f elf64 runme.asm
