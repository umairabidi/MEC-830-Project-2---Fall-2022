// Code for Task 1
// November 20, 2022
// Author: Umair Abidi
// Date of Last Change: November 20 2022
// Future Changes: Increasing Motor output speed to allow for faster movement of system
// High Level Code Description: Allows user to control system with remote control via IR mapping. Can turn clockwise, counterclockwise and move up and down

#include <AccelStepper.h>
#include <IRremote.h>
#include <Stepper.h>

#define FULLSTEP 4
#define FORWARD				0xFF629D // IR Sensor Mapping Codes that correspond to Manual Remote Control
#define BACKWARDS			0xFFA857
#define CLOCKWISE			0xFFC23D
#define COUNTERCLOCKWISE	0xFF22DD

#define wheel_radius 27		// mm
#define wheelbase 140.1		// mm

AccelStepper stp_R(FULLSTEP, A0, A2, A1, A3);
AccelStepper stp_L(FULLSTEP, 7, 9, 8, 10);
Stepper stp_R2(2038, A0, A2, A1, A3);
Stepper stp_L2(2038, 7, 9, 8, 10);

int state = 0;

#define receive_pin 2
IRrecv irrecv(receive_pin);
decode_results results;
int IR_Button;

long req_steps(long distance);
void rotate(double angle);

unsigned long prevTime = 0;

void setup() {


	stp_L2.setSpeed(10);
	stp_R2.setSpeed(10);
	
	irrecv.enableIRIn();
	Serial.begin(9600);
}

void loop() {

	if (irrecv.decode(&results)){
        Serial.println(results.value,HEX);
        Serial.println(results.value);
        irrecv.resume(); 
        IR_Button = results.value;
    }

	switch (IR_Button){
		case FORWARD:
			for (int i=0; i<150; i++){
				stp_L2.step(-1);
				stp_R2.step(1);
			}
			break;
		case BACKWARDS:
			for (int i=0; i<150; i++){
				stp_L2.step(1);
				stp_R2.step(-1);
			}
			break;
		case CLOCKWISE:
			rotate(-5);
			break;
		case COUNTERCLOCKWISE:
			rotate(5);
			break;
	}
	IR_Button = 0;

	if (millis() - prevTime >= 500){
		Serial.print(stp_L.distanceToGo());
		Serial.print("\t");
		Serial.println(stp_L.currentPosition());
		
		Serial.print(stp_R.distanceToGo());
		Serial.print("\t");
		Serial.println(stp_R.currentPosition());
		prevTime = millis();
	}
//	stp_L.disableOutputs();
//	stp_R.disableOutputs();
}

long req_steps(long distance){
	return (1.0/wheel_radius)*(63.68395062)*(16)*(1/3.1415926535)*distance;
}
void rotate(double angle){
	long req = req_steps(angle*(wheelbase/2.0)*(3.1415926535/180));
	for (int i=0; i<abs(req); i++){
		stp_L2.step(1*(angle/abs(angle)));
		stp_R2.step(1*(angle/abs(angle)));
	}
}
