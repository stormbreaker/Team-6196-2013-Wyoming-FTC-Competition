#pragma config(Hubs, S1, HTMotor, HTServo, HTMotor, none)
#pragma config(Sensor, S1, , sensorI2CMuxController)
#pragma config(Motor, mtr_S1_C1_1, rightDrive, tmotorTetrix, openLoop)
#pragma config(Motor, mtr_S1_C1_2, leftDrive, tmotorTetrix, openLoop, reversed)
#pragma config(Motor, mtr_S1_C3_2, arm, tmotorTetrix, openLoop, reversed)
#pragma config(Servo, srvo_S1_C2_1, grabber, tServoStandard)

#include "JoystickDriver.c"

void initializeRobot() {
  servo[grabber] = 200;
  return;
}

task main() {
  initializeRobot();
  waitForStart();

  motor[arm] = 30;
  wait1Msec(300);
  motor[arm] = 0;
  servo[grabber] = 0;

  motor[rightDrive] = 100;
  motor[leftDrive] = 100;
  wait1Msec(1500);
  motor[rightDrive] = 0;
  motor[leftDrive] = 0;
  while(true) {}
}
