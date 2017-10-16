#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include "GPIO.h"

GPIO::GPIO(int number) {
	// GPIO device files will follow the format
	//
	//sys/class/gpio/gpio<NR>/value
	// <NR> has to be replaced with the actual device number passed as an
	// argument to the class constructor.
	char device_name[128];

	sprintf(device_name, "/sys/class/gpio/gpio%d/value", number);

	// Open special device file and store file descriptor in class member.
	fd = open(device_name, O_WRONLY);

	if (fd < 0) {
		std::cerr << "Cannot open " << device_name <<
		" - forgot sudo?  \n";
		exit(1);
	}
}

GPIO::~GPIO() {
	// Close open file descriptor
	close(fd);
}

void GPIO::GeneratePWM(int period, int pulse, int num_periods) {
	// Generate num_perios of the PWM signal
	for (int i = 0; i < num_periods; i++) {
		// Write ASCII character "1" to raise pin to 1, starting the
		// ON cycle, then wait duration of pulse.
		write(fd, "1", 1);
		usleep(pulse);
		// Write ASCII character "0" to lower pin to 0, starting the
		// OFF cycle, then wait the rest of the period time.
		write(fd, "0", 1);
		usleep(period - pulse);
	}
}
