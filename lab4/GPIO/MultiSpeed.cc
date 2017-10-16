#include <iostream>
#include <stdlib.h>
#include "GPIO.h"

int pulse(int theta) {
	return (int) (1500 + (theta - 90) * (6 + 2.0 / 3.0));
}

int main() {
	int servo1;
	int servo2;
	int initial1;
	int final1;
	int initial2;
	int final2;
	int speed1;
	int speed2;

	std::cout << "Enter a number between 1 and 5: \n1: base\n2: bicep\n3: elbow\n4: wrist\n5: gripper.";
	std::cin >> servo1;

	std::cout << "Enter an initial angle between 20 and 160.";
	std::cin >> initial1;

	std::cout << "Enter a final angle between 20 and 160.";
	std::cin >> final1;

	std::cout << "Enter a rotational speed in degrees/second";
	std::cin >> speed1;

    std::cout << "Enter a number between 1 and 5: \n1: base\n2: bicep\n3: elbow\n4: wrist\n5: gripper.";
	std::cin >> servo2;

	std::cout << "Enter an initial angle between 20 and 160.";
	std::cin >> initial2;

	std::cout << "Enter a final angle between 20 and 160.";
	std::cin >> final2;

	std::cout << "Enter a rotational speed in degrees/second";
	std::cin >> speed2;

	if (servo1 < 1 || servo1 > 5 ||
		initial1 < 20 || initial1 > 160 ||
		final1 < 20 || final1 > 160) {
		std::cout << "Invalid parameters.";
		return 1;
	}

	if (servo2 < 1 || servo2 > 5 ||
		initial2 < 20 || initial2 > 160 ||
		final2 < 20 || final2 > 160) {
		std::cout << "Invalid parameters.";
		return 1;
	}
	
	int pin1;
	switch(servo1) {
		case 1:
			pin1 = 13;
			break;
		case 2:
			pin1 = 10;
			break;
		case 3:
			pin1 = 11;
			break;
		case 4:
			pin1 = 12;
			break;
		case 5:
			pin1 = 0;
			break;
		default:
			std::cout << "Invalid servo";
			return 1;
	}	

	int pin2;
	switch(servo2) {
		case 1:
			pin2 = 13;
			break;
		case 2:
			pin2 = 10;
			break;
		case 3:
			pin2 = 11;
			break;
		case 4:
			pin2 = 12;
			break;
		case 5:
			pin2 = 0;
			break;
		default:
			std::cout << "Invalid servo";
			return 1;
	}	

	GPIO gpio1(pin1);
	GPIO gpio2(pin2);

	float delta = 0;
	float curr_angle1 = initial1;
	float curr_angle2 = initial2;
	while(true) {
		gpio1.GeneratePWM(10000, pulse(curr_angle1), 1);
		gpio2.GeneratePWM(10000, pulse(curr_angle2), 1);

		curr_angle1 += speed1 * delta;
		curr_angle2 += speed2 * delta;
		delta += 0.02;
	}

	return 0;
}
