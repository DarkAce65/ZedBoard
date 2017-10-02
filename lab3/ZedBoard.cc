#include "ZedBoard.h"

ZedBoard::ZedBoard() {
	this->fd = open("/dev/mem", O_RDWR);
	this->ptr = (char *) mmap(
		NULL,
		gpio_size,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		this->fd,
		gpio_address);
}

ZedBoard::~ZedBoard() {
	munmap(this->ptr, gpio_size);
	close(this->fd);
}

void ZedBoard::registerWrite(int offset, int value) {
	* (int *) (this->ptr + offset) = value;
}

int ZedBoard::registerRead(int offset) {
	return * (int *) (this->ptr + offset);
}

void ZedBoard::setLedState(int led_index, int state) {
	int offset;
	switch(led_index) {
		case 0:
			offset = gpio_led1_offset;
			break;
		case 1:
			offset = gpio_led2_offset;
			break;
		case 2:
			offset = gpio_led3_offset;
			break;
		case 3:
			offset = gpio_led4_offset;
			break;
		case 4:
			offset = gpio_led5_offset;
			break;
		case 5:
			offset = gpio_led6_offset;
			break;
		case 6:
			offset = gpio_led7_offset;
			break;
		case 7:
			offset = gpio_led8_offset;
			break;
		default:
			return;
	}
	* (int *) (this->ptr + offset) = state;
}
