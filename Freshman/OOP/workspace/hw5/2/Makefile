all: main.o
	g++ main.o -o main -std=c++11

main.o:main.cpp func.h linearfunc.h expfunc.h constfunc.h compfunc.h combfunc.h
	g++ -o main.o -c main.cpp -std=c++11


clean:
	rm main *.o