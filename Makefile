all: sTalk.c
	gcc -c sTalk.c List.c
	gcc -o s-talk -pthread sTalk.o List.o
clean:
	-rm -f *.o run
