all: main
main: num.o a.o num.h
	g++ num.cpp a.cpp -o test
num.o: num.h num.cpp
	g++ -c num.cpp -o num.o
a.o: num.h a.cpp
	g++ -c a.cpp -o a.o
clean:
	rm *.o