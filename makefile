main: obj/main.o obj/laska.o obj/structures.o
	gcc -o main obj/main.o obj/laska.o obj/structures.o -Wall -ansi -pedantic -Wno-unused-result

obj/main.o: src/main.c
	gcc -c src/main.c -o obj/main.o

obj/laska.o: src/laska.h src/laska.c
	gcc -c src/laska.c -o obj/laska.o

obj/structures.o: src/structures.h src/structures.c
	gcc -c src/structures.c -o obj/structures.o
