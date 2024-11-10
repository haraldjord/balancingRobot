#include <Arduino.h>

// include project files
#include "motor.h"
#include "imu_v2.h"
#include "menu.h"
#include "pid.h"



// Controller parameters 
#define PID_KP  800//2.0f
#define PID_KI  200//f
#define PID_KD  0//0.25f

#define PID_TAU 0.02f

#define PID_LIM_MIN -1023//-10.0f
#define PID_LIM_MAX  1023//10.0f

#define PID_LIM_MIN_INT -500//-5.0f
#define PID_LIM_MAX_INT  500//5.0f

#define SAMPLE_TIME_S 0.01f

// Maximum run-time of simulation 
#define SIMULATION_TIME_MAX 4.0f



// Initialise PID controller 
PIDController pid = {   PID_KP, PID_KI, PID_KD,
                        PID_TAU,
                        PID_LIM_MIN, PID_LIM_MAX,
                        PID_LIM_MIN_INT, PID_LIM_MAX_INT,
                        SAMPLE_TIME_S   };

IMU_Values imu; // calculated angel data



int i;
bool newCommand;
float setpoint = 0;
unsigned long previousMillis = 0;
unsigned interval = 100;
unsigned long readCommand = 5000;
float measurement;
char str[40];


void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  Serial.println("------ Start Balancing robot debugger --------");
  Serial.println("enter menue by sending: 1");

  initMotor();
  initIMU();
  PIDController_Init(&pid);
  //calibrateIMU(&imu);

  //imu.dt = 0.01;
  //imu.alpha = 0.2;
}



void loop() {
  // put your main code here, to run repeatedly:

newCommand = getCommand(&pid);
if(newCommand){
  printPIDController_values(&pid);
}

if (millis() - previousMillis > interval){
  previousMillis+= interval;
  

  getTilt(&imu);
  //testIMU();
  //sprintf(str, "%lu , %f , %f , %f", millis(), imu.theta_accel, imu.theta_gyro, imu.theta_filt);
  //Serial.println(str);
  //Serial.println(imu.theta_gyro);
  //Serial.println("hello!");

  //PIDController_Update(&pid, setpoint, measurement);

  }
}

