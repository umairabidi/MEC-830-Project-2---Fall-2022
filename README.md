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
