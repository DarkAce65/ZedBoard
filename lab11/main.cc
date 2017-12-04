#include "RoboticArm.h"
#include <unistd.h>

int main() {
    RoboticArm robotic_arm;

    while(true) {
        robotic_arm.MoveServo(4, 45, 45);
        robotic_arm.MoveServo(3, 45, 45);
        sleep(1);

        robotic_arm.MoveServo(4, 90, 45);
        robotic_arm.MoveServo(3, 90, 45);
        sleep(1);
    }
}
