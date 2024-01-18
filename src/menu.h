#include "pid.h"

typedef struct t_pid
{
  float Kp;
  float Ki;
  float Kd;
};

//void setPIDconstant(PIDController *pid);

bool getCommand(PIDController *pid);
