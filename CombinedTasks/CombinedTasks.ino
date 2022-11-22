#include <AccelStepper.h>
#include <IRremote.h>
#include <Stepper.h>

#define FORWARD				0xFF629D
#define BACKWARDS			0xFFA857
#define CLOCKWISE			0xFFC23D
#define COUNTERCLOCKWISE	0xFF22DD
#define IR_ONE				0xFF30CF
#define IR_TWO				0xFF18E7
#define IR_THREE			0xFF7A85
#define IR_FOUR				0xFF10EF

#define STATE1_STRAIGHT_FORWARD		10
#define STATE2_TURN_RIGHT			11
#define STATE3_STRAIGHT_RIGHT		12
#define STATE4_TURN_LEFT			13
#define STATE5_STRAIGHT_FORWARD		14

#define TASK1_MANUAL				20
#define TASK2_AUTO					21
#define TASK3_OBSTACLE				22
#define TASK4_SQUARE				23

#define wheel_radius 27		// mm
#define wheelbase 140.1		// mm
#define _6L 200

AccelStepper stp_R(FULLSTEP, A0, A2, A1, A3);
AccelStepper stp_L(FULLSTEP, 7, 9, 8, 10);
Stepper stp_R2(2038, A0, A2, A1, A3);
Stepper stp_L2(2038, 7, 9, 8, 10);

int state = 0;
int task = TASK1_MANUAL;		// Initial task
unsigned long prevTime = 0;

#define receive_pin 2
IRrecv irrecv(receive_pin);
decode_results results;
int IR_Button;

IRrecv irrecv(receive_pin);
decode_results results;
int IR_Button;

void setup() {
	// For autonomous tasks
	stp_R.setMaxSpeed(700);
	stp_R.setAcceleration(50);
	stp_L.setMaxSpeed(700);
	stp_L.setAcceleration(50);

	// For Task 1
	stp_L2.setSpeed(10);
	stp_R2.setSpeed(10);

	irrecv.enableIRIn();
	Serial.begin(9600);
}

void loop(){
	if (irrecv.decode(&results)){
        Serial.println(results.value,HEX);
        Serial.println(results.value);
        irrecv.resume(); 
        IR_Button = results.value;
    }
	switch(IR_Button){
		case IR_ONE:
			task = TASK1_MANUAL;
			Serial.println("Going to Task 1");
			break;
		case IR_TWO:
			task = TASK2_AUTO
			Serial.println("Going to Task 2");
			break;
		case IR_THREE:
			task = TASK3_OBSTACLE;
			Serial.println("Going to Task 3");
			break;
		case IR_FOUR:
			task = TASK4_SQUARE;
			Serial.println("Going to Task 4");
			break;
	}
	
	switch(task){
		case TASK1_MANUAL:
			break;
		case TASK2_AUTO:
			break;
		case TASK3_OBSTACLE:
			break;
		case TASK4_SQUARE:
			break;
	}
}


long req_steps(long distance){
	return (distance * 12.01258);
}
void rotate(double angle){
	//long req = req_steps(angle*(wheelbase/2.0)*(3.1415926535/180));
	long req = req_steps(angle*wheelbase*0.0087266462));
	for (int i=0; i<abs(req); i++){
		stp_L2.step(1*(angle/abs(angle)));
		stp_R2.step(1*(angle/abs(angle)));
	}
}
