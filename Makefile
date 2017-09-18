CXXFLAGS=-Wall -lstdc++ -std=c++0x

all: menu

bin:
	mkdir -p bin

menu: bin menu.cc
	g++ $(CXXFLAGS) menu.cc -o bin/menu

clean:
	rm -f bin/*
