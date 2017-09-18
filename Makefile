CXXFLAGS=-Wall -lstdc++ -std=c++0x

all: menu

bin:
	mkdir -p bin
	
menu: bin menu.cc
	g++ $(CXXFLAGS) Vector/Vector.cpp menu.cc -o bin/menu

clean:
	rm -f bin/*
