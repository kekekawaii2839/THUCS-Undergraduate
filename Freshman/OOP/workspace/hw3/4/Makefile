all: exe_1 exe_2 exe_3 exe_4

exe_1: main.cpp Rack.cpp Rack.h
	g++ main.cpp Rack.cpp -o exe_1 -std=c++11 -DTASK1

exe_2: main.cpp Rack.cpp Rack.h
	g++ main.cpp Rack.cpp -o exe_2 -std=c++11 -DTASK2

exe_3: main.cpp Rack.cpp Rack.h
	g++ main.cpp Rack.cpp -o exe_3 -std=c++11 -DTASK3

exe_4: main.cpp Rack.cpp Rack.h
	g++ main.cpp Rack.cpp -o exe_4 -std=c++11 -DTASK4

clean:
	rm exe*