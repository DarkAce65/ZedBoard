#include "RoboticArm.h"
#include <unistd.h>

int main() {
    RoboticArm robotic_arm;

	robotic_arm.MoveServo(1, 35, 30);
	sleep(6);
	robotic_arm.MoveServo(4, 0, 45);
	sleep(1);

	robotic_arm.MoveServo(1, 135, 200);
	robotic_arm.MoveServo(2, 165, 150);
	usleep(500000);
	robotic_arm.MoveServo(4, 100, 255);
}
