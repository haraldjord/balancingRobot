#ifndef MOTOR_H
#define MOTOR_H



void initMotor(void);

void motorDirection(bool left, bool right);

void motorSpeed(char left, char right);

void motorSpeedTest(char speed);

#endif