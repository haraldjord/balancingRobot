#ifndef IMU_V2_H
#define IMU_V2_H

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

typedef struct 
{
    /* data */
    float x;
    float y;
    float z;
}Vector;

typedef struct 
{
    Vector accel;
    Vector gyro;   
    Vector accelOffset;
    Vector gyroOffset;
}MPUdata;

static void readAccel(MPUdata *mpu);

static void readGyro(MPUdata *mpu);

void calculate_IMU_error(MPUdata *imu);

void initIMU(void);

void testIMU(void);

void getTilt(IMU_Values *imu);





#endif