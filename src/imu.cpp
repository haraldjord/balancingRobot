#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <math.h>


#include "imu.h"


Adafruit_MPU6050 mpu;

void initIMU(void){
    if (!mpu.begin()){
        Serial.println("Failed to find MPU6050");
        while(1)
            delay(10);
    }

    mpu.setHighPassFilter(MPU6050_HIGHPASS_5_HZ);
    mpu.setMotionDetectionDuration(10);


}


float getTilt(bool printAngle){

    float theta;
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    theta = -atan(a.acceleration.x/a.acceleration.z);

    if (printAngle){
        Serial.print("theta: \t");
        Serial.print("radian = ");
        Serial.print(theta);
        Serial.print("\tangle = ");
        Serial.println(theta*180/PI);
    }
    return theta;

}



void printIMU(void){

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

Serial.print("AccelX:");
Serial.println(a.acceleration.x);
}



