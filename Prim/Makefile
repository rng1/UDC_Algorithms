prim: main.o queue.o
	gcc main.o queue.o -o prim

main.o: prim.c
	gcc -c prim.c

queue.o: queue.c queue.h
	gcc -c queue.c
