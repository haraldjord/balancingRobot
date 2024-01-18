#include <Arduino.h>

// include project files
#include "motor.h"
#include "imu.h"
#include "menu.h"
#include "pid.h"



//Adafruit_MPU6050 mpu;
/* Controller parameters */
#define PID_KP  150//2.0f
#define PID_KI  0//f
#define PID_KD  0//0.25f

#define PID_TAU 0.02f

#define PID_LIM_MIN -255//-10.0f
#define PID_LIM_MAX  255//10.0f

#define PID_LIM_MIN_INT -150//-5.0f
#define PID_LIM_MAX_INT  150//5.0f

#define SAMPLE_TIME_S 0.01f

/* Maximum run-time of simulation */
#define SIMULATION_TIME_MAX 4.0f



/* Initialise PID controller */
PIDController pid = {   PID_KP, PID_KI, PID_KD,
                        PID_TAU,
                        PID_LIM_MIN, PID_LIM_MAX,
                        PID_LIM_MIN_INT, PID_LIM_MAX_INT,
                        SAMPLE_TIME_S   };



bool newCommand;
float measurement;
float setpoint = 0;







void setup() {
Serial.begin(115200);
while (!Serial)
  delay(10);

Serial.println("------ Start Balancing robot debugger --------");
Serial.println("enter menue by sending: 1");





initMotor();
initIMU();
PIDController_Init(&pid);
}








void loop() {
  // put your main code here, to run repeatedly:

//printIMU();
measurement = getTilt(false);
newCommand = getCommand(&pid);
if(newCommand){
  printPIDController_values(&pid);
  }


/* Compute new control signal */
PIDController_Update(&pid, setpoint, measurement);

// update output
motorSpeedTest(char(abs((pid.out))));
Serial.println(((pid.out)));
Serial.println(int(abs(pid.out)));




delay(100);


}
