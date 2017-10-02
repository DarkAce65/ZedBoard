#ifndef WIIMOTE_H
#define WIIMOTE_H

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

class Wiimote {
private:
	int fd;

public:
	Wiimote();
	~Wiimote();
	
	void listen();
	virtual void accelerationEvent(int code, int acceleration);
};

#endif
