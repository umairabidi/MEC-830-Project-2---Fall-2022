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

#define POWER						9

#define TASK1_MANUAL				91
#define TASK2_AUTO					92
#define TASK3_OBSTACLE				93
#define TASK4_SQUARE				94

#define TASK2_STATE1_STRAIGHT_FORWARD	21
#define TASK2_STATE2_TURN_RIGHT			22
#define TASK2_STATE3_STRAIGHT_RIGHT		23
#define TASK2_STATE4_TURN_LEFT			24
#define TASK2_STATE5_STRAIGHT_FORWARD	25

#define TASK3_STATE1_FORWARD			31
#define TASK3_STATE2_AVOID				32
#define TASK3_STATE3_FORWARD			33

#define TASK4_STATE1_STRAIGHT_FORWARD	41
#define TASK4_STATE2_TURN_RIGHT			42
#define TASK4_STATE3_STRAIGHT_RIGHT		43
#define TASK4_STATE4_TURN_RIGHT			44
#define TASK4_STATE5_STRAIGHT_DOWN		45
#define TASK4_STATE6_TURN_RIGHT			46
#define TASK4_STATE7_STRAIGHT_LEFT		47
#define TASK4_DONE						48

#define wheel_radius 27			// mm, radius of the driving wheel
#define wheelbase 137.1			// mm, distance between traction lines
#define _6L 200					// mm, 6L as defined in the lab manual (6∙165.5 mm)
#define DistPerButton  20		// mm, the distance to travel straight for every button press
#define AnglePerButton 10		// degrees, the angle to rotate about for every button press

#define FULLSTEP 4
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

long req_steps(long distance);
long rotate_step(double angle);

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

long req_steps(long distance);	// Computes the number of stepper steps required for linear distance
long rotate_steps(double angle);	// Returns the number of steps to rotate the car about angle.

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
			task = TASK2_AUTO;
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
		case POWER:
			break;		// Have the green LED turn off in this state, and turn on in all other states
		case TASK1_MANUAL:
			// Task 1 uses the regular stepper library without implementing acceleration.
				switch (IR_Button){
					case FORWARD:
						for (int i=0; i<req_steps(DistPerButton); i++){
							stp_L2.step(-1);
							stp_R2.step(1);
						}
						break;
					case BACKWARDS:
						for (int i=0; i<req_steps(DistPerButton); i++){
							stp_L2.step(1);
							stp_R2.step(-1);
						}
						break;
					case CLOCKWISE:
						for (int i=0; i<rotate_steps(AnglePerButton); i++){
							stp_L2.step(-1);
							stp_R2.step(-1);
						}
						break;
					case COUNTERCLOCKWISE:
						for (int i=0; i<rotate_steps(AnglePerButton); i++){
							stp_L2.step(1);
							stp_R2.step(1);
						}
						break;
				}
			break;
		case TASK2_AUTO:
			switch (state){
				case STATE1_STRAIGHT_FORWARD:
					stp_L.moveTo(-req_steps(_6L));
					stp_R.moveTo(req_steps(_6L));
					break;
				case STATE2_TURN_RIGHT:
					stp_L.moveTo(-rotate_steps(-90));
					stp_R.moveTo(rotate_steps(-90));
					break;
				case STATE3_STRAIGHT_RIGHT:
					stp_L.moveTo(-req_steps(_6L));
					stp_R.moveTo(req_steps(_6L));
					break;
				case STATE4_TURN_LEFT:
					stp_L.moveTo(-rotate_steps(90));
					stp_R.moveTo(rotate_steps(90));
					break;
				case STATE5_STRAIGHT_FORWARD:
					stp_L.moveTo(-req_steps(_6L));
					stp_R.moveTo(req_steps(_6L));
					break;	
			}
			break;
		case TASK3_OBSTACLE:
			break;
		case TASK4_SQUARE:
			switch(state){
				case TASK4_STATE1_STRAIGHT_FORWARD:
					stp_L.moveTo(-req_steps(_6L));
					stp_R.moveTo(req_steps(_6L));
					break;
				case TASK4_STATE2_TURN_RIGHT:
					stp_L.moveTo(-rotate_steps(-90));
					stp_R.moveTo(rotate_steps(-90));
					break;
				case TASK4_STATE3_STRAIGHT_RIGHT:
					stp_L.moveTo(-req_steps(_6L));
					stp_R.moveTo(req_steps(_6L));
					break;
				case TASK4_STATE4_TURN_RIGHT:
					stp_L.moveTo(-rotate_steps(-90));
					stp_R.moveTo(rotate_steps(-90));
					break;
				case TASK4_STATE5_STRAIGHT_DOWN:
					stp_L.moveTo(-req_steps(_6L));
					stp_R.moveTo(req_steps(_6L));
					break;
				case TASK4_STATE6_TURN_RIGHT:
					stp_L.moveTo(-rotate_steps(-90));
					stp_R.moveTo(rotate_steps(-90));
					break;
				case TASK4_STATE7_STRAIGHT_LEFT:
					stp_L.moveTo(-req_steps(_6L));
					stp_R.moveTo(req_steps(_6L));
				case 
			break;
	}
	
	if (task != TASK1_MANUAL){		// This is accelstepper, not used for Task 1
		stp_L.run();
		stp_R.run();
	}

	if ((stp_L.distanceToGo()==0)&&(stp_R.distanceToGo()==0)){			// If both motors have reached the required steps. 
		stp_L.setCurrentPosition(0);
		stp_R.setCurrentPosition(0);
		state++;
	}

	
	IR_Button = 0;
}

long req_steps(long distance){
	return (distance * 12.01258);
}
long rotate_steps(double angle){
	//long req = req_steps(angle*(wheelbase/2.0)*(3.1415926535/180));
	return req_steps(angle*wheelbase*0.0087266462);
}