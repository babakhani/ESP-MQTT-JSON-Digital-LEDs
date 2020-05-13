#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <AFMotor.h> 

int hallSensorPin = 2;     
int state = 0;    

int motorsspeed = 220;
int trundelay = 1000;
int turnbackdelay = 2000;
bool during_turn = false;
bool lastrotateclw = false;

AF_DCMotor motor_right(2, MOTOR12_1KHZ);
AF_DCMotor motor_rare_right(3, MOTOR34_1KHZ);
AF_DCMotor motor_left(1, MOTOR12_1KHZ);
AF_DCMotor motor_rare_left(4, MOTOR34_1KHZ);


void stop(void) {
	motor_right.run(RELEASE);
	motor_left.run(RELEASE);
	motor_rare_right.run(RELEASE);
	motor_rare_left.run(RELEASE);
}

void go_forward(void) {
	motor_right.run(FORWARD);
	motor_left.run(FORWARD);
	motor_rare_right.run(FORWARD);
	motor_rare_left.run(FORWARD);
}

void go_backward(void) {
	motor_right.run(BACKWARD);
	motor_left.run(BACKWARD);
	motor_rare_right.run(BACKWARD);
	motor_rare_left.run(BACKWARD);
}

void turn_right(void) {
	motor_right.run(BACKWARD);
	motor_rare_right.run(BACKWARD);
	motor_left.run(FORWARD);
	motor_rare_left.run(FORWARD);
	delay(trundelay);
	stop();
}

void turn_left(void) {
	motor_left.run(BACKWARD);
	motor_rare_left.run(BACKWARD);
	motor_right.run(FORWARD);
	motor_rare_right.run(FORWARD);
	delay(trundelay);
	stop();
}

void turn_back(void) {
	during_turn = true;
	///if (lastrotateclw) {
	///  motor_left.run(BACKWARD);
	///  motor_rare_left.run(BACKWARD);
	///  motor_right.run(FORWARD);
	///  motor_rare_right.run(FORWARD);
	///  lastrotateclw = false;
	///} else {
	///  motor_left.run(FORWARD);
	///  motor_rare_left.run(FORWARD);
	///  motor_right.run(BACKWARD);
	///  motor_rare_right.run(BACKWARD);
	///  lastrotateclw = true;
	///}
	go_forward();
	delay(200);
	stop();
	delay(200);
	go_backward();
	delay(200);
	go_forward();
	delay(200);
	stop();
	delay(200);
	go_backward();
	delay(200);
	stop();
	during_turn = false;
}

void setup(void) {
	pinMode(hallSensorPin, INPUT);  
	Serial.begin(115200);
	motor_right.setSpeed(motorsspeed);
	motor_left.setSpeed(motorsspeed);
	motor_rare_right.setSpeed(motorsspeed);
	motor_rare_left.setSpeed(motorsspeed);
}
void loop(void) {
   
	//go_forward();
	//delay(1000);
    //go_backward();
	//delay(1000);
	state = digitalRead(hallSensorPin);
	if (state == LOW && !during_turn) {
		//turn_back();
	}
	else if (!during_turn){
		stop();
	}
}




