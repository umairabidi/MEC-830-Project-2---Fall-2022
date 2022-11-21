#include <Stepper.h>

Stepper stp_R(2048, A0, A2, A1, A3);
Stepper stp_L(2048, 7, 9, 8, 10);

void setup() {
	stp_R.setSpeed(15);
	stp_L.setSpeed(15);
}

void loop() {
	for (int i=0; i<1000; i++){
		stp_R.step(1);
		stp_L.step(-1);
	}
}
