#include <Arduino.h>
#include "motor.h"



#define enA 9
#define enB 10
#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4

void initMotor(void){
// Set pinMode
pinMode(enA, OUTPUT);
pinMode(enB, OUTPUT);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);


motorDirection(true, true);
motorSpeed(255, 255);

}


void motorDirection(bool left, bool right){ // true = forward and false = backward
/*
left = enB, IN3, IN4
right = enA, IN1, IN2
*/
if (left){
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}
else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}
if (right) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    
} 
else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
}
}

void motorSpeed(char left, char right){
    /*Motor speed 0-255*/
    analogWrite(enB, left);
    analogWrite(enA, right);
}


void motorSpeedTest(char speed){
    if (speed>0)
        motorDirection(true, true);
    else
        motorDirection(false, false);
    analogWrite(enB, speed);
    analogWrite(enA, speed);
}