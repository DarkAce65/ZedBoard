#ifndef WIIMOTE_H
#define WIIMOTE_H

class Wiimote {
private:
	int fd;
	
public:
	Wiimote();
	~Wiimote();
	
	void listen();
	void buttonEvent(int code, int value);
};

#endif
