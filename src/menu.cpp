#include<Arduino.h>
#include "menu.h"
#include "pid.h"




//t_pid pid;


/*
void setPIDconstant(PIDController *pid){
  Serial.println("what would you like to change? \nKp: 1 \nKi: 2 \nKd: 3\n");
  while(Serial.available()==0){}
  String commandtxt = Serial.readStringUntil('\n');
  int command = commandtxt.toInt();
  if (command==1){
    Serial.print("Kp = ");
    Serial.print(pid->Kd);
    Serial.println("\tenter new kp value:");
    while(Serial.available()==0){}
    String command = Serial.readStringUntil('\n');
    pid->Kp = command.toFloat();
    Serial.print("New kp value: ");
    Serial.println(pid->Kp);
  }
  else if(command==2){
    Serial.print("Ki = ");
    Serial.print(pid->Ki);
    Serial.println("\tenter new ki value:");
    while(Serial.available()==0){}
    String command = Serial.readStringUntil('\n');
    pid->Ki = command.toFloat();
    Serial.print("New ki value: ");
    Serial.println(pid->Ki);
  }
  else if (command==3){
    Serial.print("Kd = ");
    Serial.print(pid->Kd);
    Serial.println("\tenter new kd value:");
    while(Serial.available()==0){}
    String command = Serial.readStringUntil('\n');
    pid->Kd = command.toFloat();
    Serial.print("New kd value: ");
    Serial.println(pid->Kd);
  }
  else {
    Serial.println("command not applicable, try again... \n\n");
    setPIDconstant(pid);
  }
}
*/


bool getCommand(PIDController *pid){
  char str[200];
    bool newCommand = false;
  if (Serial.available()>0){
    String commandtxt = Serial.readStringUntil('\n');
    int command = commandtxt.toInt();
    Serial.println(command);
    if (command==0){
      Serial.println("test ok!");
    }
    if (command==1){
        newCommand = true;
        sprintf(str, "what would you like to change? \nKp: 1 (%f) \nKi: 2 (%f) \nKd: 3 (%f)\nout: 4 (%f)", pid->Kp, pid->Ki, pid->Kd, pid->out);
        Serial.println(str);
  while(Serial.available()==0){}
  String commandtxt = Serial.readStringUntil('\n');
  int command = commandtxt.toInt();
  if (command==1){
    Serial.print("Kp = ");
    Serial.print(pid->Kd);
    Serial.println("\tenter new kp value:");
    while(Serial.available()==0){}
    String command = Serial.readStringUntil('\n');
    pid->Kp = command.toFloat();
    Serial.print("New kp value: ");
    Serial.println(pid->Kp);
  }
  else if(command==2){
    Serial.print("Ki = ");
    Serial.print(pid->Ki);
    Serial.println("\tenter new ki value:");
    while(Serial.available()==0){}
    String command = Serial.readStringUntil('\n');
    pid->Ki = command.toFloat();
    Serial.print("New ki value: ");
    Serial.println(pid->Ki);
  }
  else if (command==3){
    Serial.print("Kd = ");
    Serial.print(pid->Kd);
    Serial.println("\tenter new kd value:");
    while(Serial.available()==0){}
    String command = Serial.readStringUntil('\n');
    pid->Kd = command.toFloat();
    Serial.print("New kd value: ");
    Serial.println(pid->Kd);
  }
    else if (command==4){
      Serial.print("out = ");
      Serial.print(pid->Kd);
      Serial.println("\tenter new pid.out value:");
      while(Serial.available()==0){}
      String command = Serial.readStringUntil('\n');
      pid->out = command.toFloat();
      Serial.print("New out value: ");
      Serial.println(pid->out);
  }
  else {
      Serial.println("command not applicable, try again... \n\n");
    }
}
  }

  return newCommand;
}




