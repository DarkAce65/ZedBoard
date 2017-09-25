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

/**
 * Write a 4-byte value at the specified general-purpose I/O location.
 *
 * @param ptr Base address returned by 'mmap'.
 * @parem offset Offset where device is mapped.
 * @param value Value to be written.
 */
void registerWrite(char *ptr, int offset, int value) {
	* (int *) (ptr + offset) = value;
} 

/**
 * Read a 4-byte value from the specified general-purpose I/O location.
 *
 * @param ptr Base address returned by 'mmap'.
 * @param offset Offset where device is mapped.
 * @return Value read.
 */
int registerRead(char *ptr, int offset) {
	return * (int *) (ptr + offset);
}

/**
 * Initialize general-purpose I/O
 * - Opens access to physical memory /dev/mem
 * - Maps memory at offset 'gpio_address' into virtual address space
 *
 * @param fd
 * File descriptor passed by reference, where the result
 * of function 'open' will be stored.
 *
 * @return
 * Address to virtual memory which is mapped to physical,
 * or MAP_FAILED on error.
 */
char *initialize(int *fd) {
	*fd = open( "/dev/mem", O_RDWR);
	return (char *) mmap(
		NULL,
		gpio_size,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		*fd,
		gpio_address);
}

/**
 * Close general-purpose I/O.
 *
 * @param ptr Virtual address where I/O was mapped.
 * @param fd File descriptor previously returned by 'open'.
 */
void finalize(char *ptr, int fd) {
	munmap(ptr, gpio_size);
	close(fd);
} 

/**
 * Show lower 8 bits of integer value on LEDs
 *
 * @param ptr Base address of I/O
 * @param value Value to show on LEDs
 */
void setLedNumber(char *ptr, int value) {
	RegisterWrite(ptr, gpio_led1_offset, value % 2);
	RegisterWrite(ptr, gpio_led2_offset, (value / 2) % 2);
	RegisterWrite(ptr, gpio_led3_offset, (value / 4) % 2);
	RegisterWrite(ptr, gpio_led4_offset, (value / 8) % 2);
	RegisterWrite(ptr, gpio_led5_offset, (value / 16) % 2);
	RegisterWrite(ptr, gpio_led6_offset, (value / 32) % 2);
	RegisterWrite(ptr, gpio_led7_offset, (value / 64) % 2);
	RegisterWrite(ptr, gpio_led8_offset, (value / 128) % 2);
}

int main() {
	// Initialize
	int fd;
	char *ptr = Initialize(&fd);
	// Check error
	if (ptr == MAP_FAILED) {
		perror("Mapping I/O memory failed - Did you run with 'sudo'?\n");
		return -1;
	}
	int value;
	std::cout << "Enter a value less than 256: ";
	std::cin >> value;
	// Show the value on the Zedboard LEDs
	SetLedNumber(ptr, value);
	// Done
	Finalize(ptr, fd);
	return 0;
}
