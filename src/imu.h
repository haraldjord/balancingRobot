

/*
#ifndef IMU_H
#define IMU_H

typedef struct
{
    // data 
    float theta_accel;
    float theta_gyro;
    float theta_filt;

    // keep on values
    float previous_theta_gyro;
    float dt;
    float alpha;

    //mpu5060 reading stuff
    float gyro_offsetY;

}IMU_Values;


void initIMU(void);

void calibrateIMU(IMU_Values *imu);

void printIMU(void);

void testfunction(float *testtt);

void getTilt(IMU_Values  *imu);




#endif
*/