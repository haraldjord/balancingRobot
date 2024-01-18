#ifndef IMU_H
#define IMU_H

typedef struct imu
{
    /* data */
    float x;
    float y;
    float z;
};


void initIMU(void);

void printIMU(void);

float getTilt(bool printAngle=false);




#endif