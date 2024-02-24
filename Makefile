clean:
	rm -rf *.o *.a StrList

Main.o: Main.c StrList.h
	gcc -c Main.c -o Main.o

StrList.o: StrList.c StrList.h
	gcc -c StrList.c -o StrList.o

libStrList.a: StrList.o
	ar -rc libStrList.a StrList.o

StrList: Main.o libStrList.a
	gcc -o StrList Main.o -L. -lStrList
