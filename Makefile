CXXFLAGS=-Wall -lstdc++ -std=c++0x

all: menu

bin:
	mkdir -p bin

menu: bin lab1/menu.cc
	g++ $(CXXFLAGS) lab1/menu.cc -o bin/menu

LedOnOff: bin lab2/LedOnOff.cc
	g++ $(CXXFLAGS) lab2/LedOnOff.cc -o bin/LedOnOff

clean:
	rm -f bin/*
