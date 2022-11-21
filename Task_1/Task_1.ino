// Code for Task 1
// November 20, 2022
// 

#include <AccelStepper.h>
#include <IRremote.h>

#define FULLSTEP 4
#define FORWARD				0xFF629D
#define BACKWARDS			0xFFA857
#define CLOCKWISE			0xFFC23D
#define COUNTERCLOCKWISE	0xFF22DD

#define wheel_radius 27		// mm
#define wheelbase 140.1		// mm

AccelStepper stp_R(FULLSTEP, A0, A2, A1, A3);
AccelStepper stp_L(FULLSTEP, 7, 9, 8, 10);

int state = 0;

#define receive_pin 2
IRrecv irrecv(receive_pin);
decode_results results;
int IR_Button;

long req_steps(long distance);
void rotate(double angle);

unsigned long prevTime = 0;

void setup() {
	stp_R.setMaxSpeed(2000);
	stp_R.setAcceleration(200);
	
	stp_L.setMaxSpeed(2000);
	stp_L.setAcceleration(200);

	stp_L.setSpeed(2000);
	stp_R.setSpeed(2000);
	
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
			stp_L.moveTo(-100);
			stp_R.moveTo(100);
			break;
		case BACKWARDS:
			stp_L.moveTo(100);
			stp_R.moveTo(-100);
			break;
		case CLOCKWISE:
			rotate(-5);
			break;
		case COUNTERCLOCKWISE:
			rotate(5);
			break;
	}
	IR_Button = 0;

	stp_L.runSpeed();
	stp_R.runSpeed();
	
	if ((stp_L.distanceToGo()==0)&&(stp_R.distanceToGo()==0)){
		stp_L.setCurrentPosition(0);
		stp_R.setCurrentPosition(0);
	}
		
	if (millis() - prevTime >= 100){
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
	stp_R.moveTo(req);
	stp_L.moveTo(req);
}
