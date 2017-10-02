#include "Wiimote.h"
#include "ZedBoard.h"

class WiimoteToLed : public Wiimote {
private:
	ZedBoard* z;

public:
	WiimoteToLed(ZedBoard* z) {
		this->z = z;
	};

	void accelerationEvent(int code, int acceleration) {
		if(code != 3) {
			return;
		}
		int truncated = std::min(std::max(-100, acceleration), 100);
		int scaled = abs(truncated) * 8 / 100;
		for(int i = 0; i < scaled; i++) {
			z->setLedState(i, 1);
		}
		for(int i = scaled; i < 8; i++) {
			z->setLedState(i, 0);
		}
	}
};

int main() {
	ZedBoard z;
	WiimoteToLed w(&z);
	w.listen();

	return 0;
}
