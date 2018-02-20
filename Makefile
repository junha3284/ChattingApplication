test: sTalk.c
	gcc -c sTalk.c List.c -pthread
	gcc -o run sTalk.o List.o
clean:
	-rm -f *.o run
