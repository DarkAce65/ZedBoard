#include "Wiimote.h"
#include "ZedBoard.h"

class WiimotePosition : public Wiimote {
private:
	ZedBoard* z;
	time_t lastPrint;
	time_t lastPoll;
	float position[3];
	float velocity[3];
	float acceleration[3];

public:
	WiimotePosition(ZedBoard* z) {
		this->z = z;
		this->lastPrint = time(0);
		this->lastPoll = time(0);
	};

	void integrateAcceleration() {
		time_t t = time(0);
		time_t delta = t - this->lastPoll;
		for(int i = 0; i < 3; i++) {
			this->velocity[i] = this->acceleration[i] * delta;
			this->position[i] = this->velocity[i] * delta;
		}
		this->lastPoll = t;
	}

	void accelerationEvent(int code, int acceleration) {
		if(code != 3 && code != 4 && code != 5) {
			return;
		}
		switch(code) {
			case 3: // X
				this->acceleration[0] = acceleration;
				break;
			case 4: // Y
				this->acceleration[1] = acceleration;
				break;
			case 5: // Z
				this->acceleration[2] = acceleration;
				break;
		}
		integrateAcceleration();
		print();
	}

	void printArray(float array[], int length) {
		std::cout << "[";
		for(int i = 0; i < length; i++) {
			std::cout << array[i];
			if(i < length - 1) {
				std::cout << ", ";
			}
		}
		std::cout << "]" << std::endl;
	}

	void print() {
		time_t t = time(0);
		if(t - this->lastPrint >= 60) {
			std::cout << "Position: ";
			printArray(this->position, 3);
			std::cout << "Velocity: ";
			printArray(this->velocity, 3);
			std::cout << "Acceleration: ";
			printArray(this->acceleration, 3);
			this->lastPrint = t;
		}
	}
};

int main() {
	ZedBoard z;
	WiimotePosition w(&z);
	w.listen();

	return 0;
}
