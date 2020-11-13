all: server
	gcc socktest.c -o socktest

clean:
	rm *.o socktest ourServer

server: asm
	gcc ourServer.c runme.o -o ourServer -lm

asm:
	nasm -f elf64 runme.asm
