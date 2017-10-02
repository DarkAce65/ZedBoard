CXXFLAGS=-Wall -lstdc++ -std=c++0x

all: main

bin:
	mkdir -p bin

main: bin main.cc
	g++ $(CXXFLAGS) Wiimote.cc main.cc -o bin/main

clean:
	rm -f bin/*
