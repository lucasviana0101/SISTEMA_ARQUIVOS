all: main.c main.h
	gcc main.c -o ../build/app

teste: main.c main.h
	gcc main.c -o ../build/app
	../build/app

debugging:
	gcc -g main.c -o ../build/app
	gdb ../build/app

teste1: main.c main.h
	gcc -g main.c -o ../build/app
	cat ../test/input1 | ../build/app > ../test/output1

teste2: main.c main.h
	gcc -g main.c -o ../build/app
	cat ../test/input2 | ../build/app > ../test/output2
	