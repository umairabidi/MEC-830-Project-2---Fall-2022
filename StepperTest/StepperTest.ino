#include <Stepper.h>

Stepper stepper_right(2048, A0, A2, A1, A3);
Stepper stepper_left(2048, 7, 9, 8, 10);

void setup() {
	stepper_right.setSpeed(15);
	stepper_left.setSpeed(15);
}

void loop() {
	for (int i=0; i<1000; i++){
		stepper_right.step(1);
		stepper_left.step(-1);
	}
	delay(1000);
}
