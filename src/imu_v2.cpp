#include <Arduino.h>
#include <Wire.h>
#include <math.h>

#include"imu_v2.h"

const int MPU6050 = 0x68; // MPU6050 I2C address
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
float elapsedTime, currentTime, previousTime;
int c = 0;
MPUdata mpu; // raw data reading 


static void readAccel(MPUdata *mpu){
    Wire.beginTransmission(MPU6050);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050, 6, true);
    mpu->accel.x = float(((Wire.read() << 8 | Wire.read())) / 16384) ;
    mpu->accel.y = float((Wire.read() << 8 | Wire.read()) / 16384) ;
    mpu->accel.z = float((Wire.read() << 8 | Wire.read()) / 16384) ;
}

unsigned short temp;
static void readGyro(MPUdata *mpu){
    Wire.beginTransmission(MPU6050);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050, 6, true);
    temp = (Wire.read() << 8 | Wire.read()); // unit rad/s 
    mpu->gyro.x = (float(temp))/131.0;
    temp = (Wire.read() << 8 | Wire.read()); // unit rad/s 
    mpu->gyro.y = (float(temp))/131.0;
    temp = (Wire.read() << 8 | Wire.read()); // unit rad/s 
    mpu->gyro.z = (float(temp))/131.0;
}



void calculate_IMU_error(MPUdata *mpu) {
  // We can call this funtion in the setup section to calculate the accelerometer and gyro data error. From here we will get the error values used in the above equations printed on the Serial Monitor.
  // Note that we should place the IMU flat in order to get the proper values, so that we then can the correct values
  // Read gyro values 200 times
  while (c < 200) {
    readGyro(mpu);
    //sum gyro reading
    mpu->gyroOffset.x = mpu->gyroOffset.x + (mpu->gyro.x);
    mpu->gyroOffset.y = mpu->gyroOffset.y + (mpu->gyro.y); // used to calc tilt...
    mpu->gyroOffset.z = mpu->gyroOffset.z + (mpu->gyro.z);
    c++;
    delay(10);
  }
  //Divide the sum by 200 to get the error value
  mpu->gyroOffset.x = mpu->gyroOffset.x / 200;
  mpu->gyroOffset.y = mpu->gyroOffset.y / 200;
  mpu->gyroOffset.z = mpu->gyroOffset.z / 200;
  c = 0;

  // Print the error values on the Serial Monitor
  char strbuf[50];
  sprintf(strbuf, "average gyro offset: x: %f \ty: %f, \t z: %f", mpu->gyroOffset.x, mpu->gyroOffset.y, mpu->gyroOffset.z);
  Serial.print(strbuf);
}



void initIMU(void){

    Wire.begin();                      // Initialize comunication
    Wire.beginTransmission(MPU6050);       // Start communication with MPU6050 // MPU=0x68
    Wire.write(0x6B);                  // Talk to the register 6B
    Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
    Wire.endTransmission(true);        //end the transmission
    delay(10);
    // Configure Accelerometer Sensitivity - Full Scale Range (default +/- 2g)
    /*
    Wire.beginTransmission(MPU6050);
    Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
    Wire.write(0x8);                  //Set the register bits as 00001000 (+/- 4g full scale range)
    Wire.endTransmission(true);
    delay(10);
    // Configure Gyro Sensitivity - Full Scale Range (default +/- 250deg/s)
    Wire.beginTransmission(MPU6050);
    Wire.write(0x1B);                   // Talk to the GYRO_CONFIG register (1B hex)
    Wire.write(0x8);                    // Set the register bits as 00001000 (500deg/s full scale)
    Wire.endTransmission(true);
    delay(20);
    */
    // Call this function if you need to get the IMU error values for your module
    calculate_IMU_error(&mpu);
    delay(20);
}



void testIMU(void){
    Wire.beginTransmission(MPU6050);
    Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
    //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
    AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
    AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
    AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value
    // Calculating Roll and Pitch from the accelerometer data
    accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58; // AccErrorX ~(0.58) See the calculate_IMU_error()custom function for more details
    accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + 1.58; // AccErrorY ~(-1.58)
    // === Read gyroscope data === //
    previousTime = currentTime;        // Previous time is stored before the actual time read
    currentTime = millis();            // Current time actual time read
    elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
    Wire.beginTransmission(MPU6050);
    Wire.write(0x43); // Gyro data first register address 0x43
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050, 6, true); // Read 4 registers total, each axis value is stored in 2 registers
    GyroX = (Wire.read() << 8 | Wire.read()) / 131.0; // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
    GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
    GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
    // Correct the outputs with the calculated error values
    //GyroX = GyroX + 0.56; // GyroErrorX ~(-0.56)
    //GyroY = GyroY - 2; // GyroErrorY ~(2)
    //GyroZ = GyroZ + 0.79; // GyroErrorZ ~ (-0.8)
    // Currently the raw values are in degrees per seconds, deg/s, so we need to multiply by sendonds (s) to get the angle in degrees
    gyroAngleX = gyroAngleX + GyroX * elapsedTime; // deg/s * s = deg
    gyroAngleY = gyroAngleY + GyroY * elapsedTime;
    yaw =  yaw + GyroZ * elapsedTime;
    // Complementary filter - combine acceleromter and gyro angle values
    roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
    pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;

    // Print the values on the serial monitor
    Serial.print(roll);
    Serial.print("/");
    Serial.print(pitch);
    Serial.print("/");
    Serial.println(yaw);


}


void getTilt(IMU_Values *imu){
    readAccel(&mpu);
    readGyro(&mpu);
   
    char strbuf[50];
    sprintf(strbuf, "mpu gyro reading: x: %f \ty: %f, \t z: %f\n", mpu.gyro.x, mpu.gyro.y, mpu.gyro.z);
    Serial.print(strbuf);
    sprintf(strbuf, "mpu accel reading: x: %f \ty: %f, \t z: %f\n", mpu.accel.x, mpu.accel.y, mpu.accel.z);
    Serial.print(strbuf);
    
    imu->theta_accel = atan(mpu.accel.x/mpu.accel.z);
    imu->theta_gyro = imu->previous_theta_gyro + mpu.gyro.y*imu->dt;

    sprintf(strbuf, "angle, gyro  %f \taccel: %f, \n", imu->gyro_offsetY, imu->theta_accel);
    Serial.print(strbuf);
}