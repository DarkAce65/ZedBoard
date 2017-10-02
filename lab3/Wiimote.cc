#include "Wiimote.h"

Wiimote::Wiimote() {
	this->fd = open("/dev/input/event2", O_RDONLY);
	if(this->fd == -1) {
		std::cerr << "Error: Could not open event file - forgot sudo?" << std::endl;
		exit(1);
	}
}

Wiimote::~Wiimote() {
	close(this->fd);
}

void Wiimote::listen() {
	while(true) {
		char buffer[32];
		read(fd, buffer, 32);

		int code = buffer[10];
		int value = buffer[12];
		buttonEvent(code, value);
	}
}

void Wiimote::buttonEvent(int code, int value) {
	std::cout << "Code = " << code << ", value = " << value << std::endl;
}
