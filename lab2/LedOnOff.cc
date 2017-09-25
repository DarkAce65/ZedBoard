#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/mman.h>
#include <stdio.h>
// Physical base address of GPIO
const unsigned gpio_address = 0x400d0000;
// Length of memory-mapped IO window
const unsigned gpio_size = 0xff;
const int gpio_led1_offset = 0x12C; // Offset for LED1
const int gpio_led2_offset = 0x130; // Offset for LED2
const int gpio_led3_offset = 0x134; // Offset for LED3
const int gpio_led4_offset = 0x138; // Offset for LED4
const int gpio_led5_offset = 0x13C; // Offset for LED5
const int gpio_led6_offset = 0x140; // Offset for LED6
const int gpio_led7_offset = 0x144; // Offset for LED7
const int gpio_led8_offset = 0x148; // Offset for LED8
const int gpio_sw1_offset = 0x14C; // Offset for Switch 1
const int gpio_sw2_offset = 0x150; // Offset for Switch 2
const int gpio_sw3_offset = 0x154; // Offset for Switch 3
const int gpio_sw4_offset = 0x158; // Offset for Switch 4
const int gpio_sw5_offset = 0x15C; // Offset for Switch 5
const int gpio_sw6_offset = 0x160; // Offset for Switch 6
const int gpio_sw7_offset = 0x164; // Offset for Switch 7
const int gpio_sw8_offset = 0x168; // Offset for Switch 8
const int gpio_pbtnl_offset = 0x16C; // Offset for left push button
const int gpio_pbtnr_offset = 0x170; // Offset for right push button
const int gpio_pbtnu_offset = 0x174; // Offset for up push button
const int gpio_pbtnd_offset = 0x178; // Offset for down push button
const int gpio_pbtnc_offset = 0x17C; // Offset for center push button

class ZedBoard {
	char *ptr;
	int fd;
public:
	ZedBoard() {
		this->fd = open("/dev/mem", O_RDWR);
		this->ptr = (char *) mmap(
			NULL,
			gpio_size,
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			this->fd,
			gpio_address);
	}

	~ZedBoard() {
		munmap(this->ptr, gpio_size);
		close(this->fd);
	}

	/**
	 * Write a 4-byte value at the specified general-purpose I/O location.
	 *
	 * @param ptr Base address returned by 'mmap'.
	 * @parem offset Offset where device is mapped.
	 * @param value Value to be written.
	 */
	void registerWrite(int offset, int value) {
		* (int *) (this->ptr + offset) = value;
	}

	/**
	 * Read a 4-byte value from the specified general-purpose I/O location.
	 *
	 * @param ptr Base address returned by 'mmap'.
	 * @param offset Offset where device is mapped.
	 * @return Value read.
	 */
	int registerRead(int offset) {
		return * (int *) (this->ptr + offset);
	}

	/** Set the state of the LED with the given index.
	 *
	 * @param ptr Base address for general-purpose I/O
	 * @parem led_index LED index between 0 and 7
	 * @param state Turn on (1) or off (0)
	 */
	void setLedState(int led_index, int state) {
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

	int readSwitch(int switch_index) {
		switch(switch_index) {
			case 0:
				return registerRead(gpio_sw1_offset);
			case 1:
				return registerRead(gpio_sw2_offset);
			case 2:
				return registerRead(gpio_sw3_offset);
			case 3:
				return registerRead(gpio_sw4_offset);
			case 4:
				return registerRead(gpio_sw5_offset);
			case 5:
				return registerRead(gpio_sw6_offset);
			case 6:
				return registerRead(gpio_sw7_offset);
			case 7:
				return registerRead(gpio_sw8_offset);
		}
		return -1;
	}

	int readDirection() {
		if(registerRead(gpio_pbtnu_offset)) {
			return 1;
		}
		if(registerRead(gpio_pbtnd_offset)) {
			return 2;
		}
		if(registerRead(gpio_pbtnl_offset)) {
			return 3;
		}
		if(registerRead(gpio_pbtnr_offset)) {
			return 4;
		}
		if(registerRead(gpio_pbtnc_offset)) {
			return 5;
		}
		return 0;
	}

	int getSwitchState() {
		int state = 0;
		for(int i = 0; i < 8; i++) {
			if(readSwitch(i)) {
				state += 0b1 << i;
			}
		}
		return state;
	}
};

int main() {
	// Initialize
	ZedBoard *z = new ZedBoard();

	int state = z->getSwitchState();

	bool pressed = false;
	while(true) {
		int direction = z->readDirection();
		if(!pressed && direction == 1) {
			pressed = true;
			state += 1;
		}
		else if(!pressed && direction == 2) {
			pressed = true;
			state -= 1;
		}
		else if(!pressed && direction == 3) {
			pressed = true;
			state <<= 1;
		}
		else if(!pressed && direction == 4) {
			pressed = true;
			state >>= 1;
		}
		else if(!pressed && direction == 5) {
			pressed = true;
			state = z->getSwitchState();
		}
		else if(direction == 0) {
			pressed = false;
		}

		for(int i = 0; i < 8; i++) {
			z->setLedState(i, (state >> i) & 1);
		}
		usleep(100 * 1000);
	}

	delete z;
	return 0;
}
