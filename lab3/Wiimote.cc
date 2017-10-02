#include "Wiimote.h"

Wiimote::Wiimote() {
	this->fd = open("/dev/input/event0", O_RDONLY);
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
		short acceleration = * (short *) (buffer + 12);
		accelerationEvent(code, acceleration);
	}
}

void Wiimote::accelerationEvent(int code, int acceleration) {
	std::cout << "Code = " << code << ", acceleration = " << acceleration << std::endl;
}
