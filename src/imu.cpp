//#include <Arduino.h>
/*
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

    mpu.setHighPassFilter(MPU6050_HIGHPASS_DISABLE);
    mpu.setMotionDetectionDuration(10);
    mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
    mpu.setGyroRange(MPU6050_RANGE_250_DEG);

}



void calibrateIMU(IMU_Values *imu){
    // make 200 measurement on gyro, and use average as offset.
    imu->gyro_offsetY = 0; 

    int i = 0;
    float offsetSum = 0;
    int n = 200;
    sensors_event_t a, g, temp;
    for (i;i<n;i++){
        mpu.getEvent(&a, &g, &temp);
        offsetSum = offsetSum + g.gyro.y;
        delay(10);
    }
    imu->gyro_offsetY = offsetSum/n;
    //Serial.print("Gyro Y offset: ");
    Serial.println(imu->gyro_offsetY);
}

sensors_event_t a, g, temp;
void getTilt(IMU_Values *imu){

    
    mpu.getEvent(&a, &g, &temp);
    
    imu->theta_accel = atan(a.acceleration.x/a.acceleration.z);
    imu->theta_gyro = g.gyro.y;
    imu->theta_gyro = imu->previous_theta_gyro + (g.gyro.y - imu->gyro_offsetY)*imu->dt;
    //Serial.println(imu->dt);
    // save prevois theta gyro for next calculation
    imu->previous_theta_gyro = imu->theta_gyro;

    //complimentary filter
    imu->theta_filt = imu->alpha*imu->theta_gyro + (1-imu->alpha)*imu->theta_accel;
     

    char txtbuff[50];    
    //sprintf(txtbuff, "Gyro Y: %f \n", g.gyro.y);
    //Serial.println(txtbuff);   
    //Serial.println(g.gyro.y); 

}



void printIMU(void){

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

Serial.print("AccelX:");
Serial.println(a.acceleration.x);
}

*/


