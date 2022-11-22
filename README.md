# Mec 830 Project 2 - SLAM Car

Group members:
* Umair Abidi
* Stephen Chavez
* Abhay Gupta

This project consists of 4 tasks. 
1. Manual control of a car to move to certain points
2. Autonomous motion of the car to the same points.
3. Obstacle Avoidance.
4. Homing accuracy

## Code Organization

IR_mapping is used to map out the buttons on the infrared remote.

StepperTest is a program used to experiment with the motion of the robot.

The controls of the IRremote has been simplified by coordinating the actions performed by the car to the positioning of the buttons. For example, the 
forward/backward action is being performed by volume up/down. Similarly, channel change buttons perform the left and right turning actions.

Ultrasonic sensor is used to avoid obstacles and the number of turns are coded into the Arduino to tell the device to turn by 5 degrees each step. This 
is being accomplished by reducing the speed of left/right tires while the other one stays the same, hence the device receiving its turn.

The manner in which the distances for autonomous naviation for Task 2 and Task 4 were determined by the length of the design itself, so the total amount of steps that an actuator takes is equal to 6 times the length of the design. 
