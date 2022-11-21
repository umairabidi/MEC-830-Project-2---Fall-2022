// Code for Task 1

// The robot's dimensions are 165.5 X 161.26 X 96.65 mm
// Therefore, L = 165.5 mm
// 6L = 993 mm = 36.78 rev
// r = 27 mm

#include <AccelStepper.h>

AccelStepper stp_R(8, A0, A2, A1, A3);
AccelStepper stp_L(8, 7, 9, 8, 10);

signed long c_pos = 0;
signed long d_pos = 36.78;

void setup() {
	stp_R.setMaxSpeed(30);
	stp_L.setMaxSpeed(30);
	stp_R.setAcceleration(1);
	stp_L.setAcceleration(1);
	stp_L.moveTo(1000);
}

void loop() {
	// Move from P0 to P1
	stp_R.run();
}
