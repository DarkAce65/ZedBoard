#include <iostream>
#include "GPIO.h"

int pulse(int theta) {
	return (int) (1500 + (theta - 90) * (6 + 2.0 / 3.0));
}

int main() {
	int servo;
	int initial;
	int final;
	int speed;

	std::cout << "Enter a number between 1 and 5: \n1: base\n2: bicep\n3: elbow\n4: wrist\n5: gripper.";
	std::cin >> servo;

	std::cout << "Enter an initial angle between 20 and 160.";
	std::cin >> initial;

	std::cout << "Enter a final angle between 20 and 160.";
	std::cin >> final;

	std::cout << "Enter a rotational speed in degrees/second";
	std::cin >> speed;

	if (servo < 1 || servo > 5 ||
		initial < 20 || initial > 160 ||
		final < 20 || final > 160) {
		std::cout << "Invalid parameters.";
		return 1;
	}
	
	int pin;
	switch(servo) {
		case 1:
			pin = 13;
			break;
		case 2:
			pin = 10;
			break;
		case 3:
			pin = 11;
			break;
		case 4:
			pin = 12;
			break;
		case 5:
			pin = 0;
			break;
		default:
			std::cout << "Invalid servo";
			return 1;
	}

	GPIO gpio(pin);
	gpio.GenerateVariablePWM(20000, pulse(initial), pulse(final), (final - initial) / (speed * 0.02));

	return 0;
}
