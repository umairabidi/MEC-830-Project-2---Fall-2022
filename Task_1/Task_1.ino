// Code for Task 1

// The robot's dimensions are 165.5 X 161.26 X 96.65 mm
// Therefore, L = 165.5 mm
// 6L = 993 mm = 36.78 rev
// r = 27 mm

#include <AccelStepper.h>
#include <MultiStepper.h>

#define FULLSTEP 4
#define wheel_radius 27		// mm
#define wheelbase 140.1
#define STATE1_STRAIGHT_FORWARD		10
#define STATE2_TURN_RIGHT			11
#define STATE3_STRAIGHT_RIGHT		12
#define STATE4_TURN_LEFT			13
#define STATE5_STRAIGHT_FORWARD		14


#define _6L 200		// desired distance in mm

AccelStepper stp_R(FULLSTEP, A0, A2, A1, A3);
AccelStepper stp_L(FULLSTEP, 7, 9, 8, 10);


int state = STATE1_STRAIGHT_FORWARD;


long req_steps(long distance);
void rotate(int angle);

unsigned long prevTime = 0;

void setup() {
	stp_R.setMaxSpeed(700);
	stp_R.setAcceleration(50);
	
	stp_L.setMaxSpeed(700);
	stp_L.setAcceleration(50);
	Serial.begin(9600);
}

void loop() {
	switch (state){
		case STATE1_STRAIGHT_FORWARD:
			stp_L.moveTo(-req_steps(_6L));
			stp_R.moveTo(req_steps(_6L));
			break;
		case STATE2_TURN_RIGHT:
			rotate(-90);
			break;
		case STATE3_STRAIGHT_RIGHT:
			stp_L.moveTo(-req_steps(_6L));
			stp_R.moveTo(req_steps(_6L));
			break;
		case STATE4_TURN_LEFT:
			rotate(90);
			break;
		case STATE5_STRAIGHT_FORWARD:
			stp_L.moveTo(-req_steps(_6L));
			stp_R.moveTo(req_steps(_6L));
			break;	
	}
	stp_L.run();
	stp_R.run();
	
	

	if ((stp_L.distanceToGo()==0)&&(stp_R.distanceToGo()==0)){
		stp_L.setCurrentPosition(0);
		stp_R.setCurrentPosition(0);
		state++;
		if (state == STATE5_STRAIGHT_FORWARD+1){
			state = STATE1_STRAIGHT_FORWARD;
		}
		delay(2000);
	}

	if (millis() - prevTime >= 200){
		Serial.println(state);
		Serial.print(stp_L.distanceToGo());
		Serial.print("\t");
		Serial.println(stp_L.currentPosition());
		
		Serial.print(stp_R.distanceToGo());
		Serial.print("\t");
		Serial.println(stp_R.currentPosition());
		prevTime = millis();
	}
	
}

long req_steps(long distance){
//	return (1.0/wheel_radius)*(32*22*26*31/8910.0)*(64)*(1/3.1415926535)*distance;
	return (distance * 12.01258);
}
void rotate(int angle){
//	long req = req_steps(angle*(wheelbase/2.0)*(3.1415926535/180));
	long req = req_steps(angle*1.1344600);
	stp_R.moveTo(req);
	stp_L.moveTo(req);
}
