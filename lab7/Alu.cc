#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>

void Write(char *ptr, unsigned offset, unsigned value) {
	* (volatile unsigned *) (ptr + offset) = value;
}

unsigned Read(char *ptr, unsigned offset) {
	return * (volatile unsigned *) (ptr + offset);
}

int main() {
	// Map memory
	int fd = open("/dev/mem", O_RDWR);
	char *ptr = (char *) mmap(NULL, 0xff, PROT_READ | PROT_WRITE,
		MAP_SHARED,
		fd,
		0x400d0000);

	// Check status
	if(ptr == (void *) -1) {
		std::cerr << "Error mapping memory - forgot sudo?\n";
		return 1;
	}

	int a, b, code;
	std::cout << "Enter the first number for the ALU: ";
	std::cin >> a;
	std::cout << "Enter the second number for the ALU: ";
	std::cin >> b;
	std::cout << "0 = addition, 1 = subtraction, 2 = multiplication, 3 = bitwise AND" << std::endl;
	std::cout << "Enter the opcode: ";
	std::cin >> code;

	Write(ptr, 0x100, a);
	Write(ptr, 0x104, b);
	Write(ptr, 0x108, code);
	std::cout << "The output is: " << Read(ptr, 0x10c) << std::endl;

	// Unmap memory
	munmap(ptr, 0xff);
	close(fd);
}
