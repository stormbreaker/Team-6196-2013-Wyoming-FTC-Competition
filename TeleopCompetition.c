#pragma config(Hubs, S1, HTMotor, HTServo, HTMotor, none)
#pragma config(Sensor, S1, , sensorI2CMuxController)
#pragma config(Motor, mtr_S1_C1_1, rightDrive, tmotorTetrix, openLoop)
#pragma config(Motor, mtr_S1_C1_2, leftDrive, tmotorTetrix, openLoop, reversed)
#pragma config(Motor, mtr_S1_C3_2, arm, tmotorTetrix, openLoop, reversed)
#pragma config(Servo, srvo_S1_C2_1, grabber, tServoStandard)

/*
 * Copyright (C) 2013 DJ Heaney
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "JoystickDriver.c"

// Scale function taken from
// http://gk12.poly.edu/amps-cbri/pdf/RobotC%20FTC%20Books/ROBOTC_Training_Guide.pdf
int scale(int joyValue) {
  const int DEADZONE = 5;
  const int MAX_MOTOR_VAL = 100;
  const float MAX_JOY_VAL = 127.0;

  if(abs(joyValue) < DEADZONE) {
    return 0;
  }

  int direction = joyValue / abs(joyValue);
  float ratio   = ((joyValue * joyValue) / (MAX_JOY_VAL * MAX_JOY_VAL));
  int scaledVal = (ratio * MAX_MOTOR_VAL) * direction;

  return scaledVal;
}

task checkDrive() {
  while(true) {
    getJoystickSettings(joystick);
    motor[rightDrive] = scale(joystick.joy1_y1);
    motor[leftDrive]  = scale(joystick.joy1_y2);
  }
}

task checkArm() {
  while(true) {
    getJoystickSettings(joystick);
    motor[arm] = scale(joystick.joy2_y2);
  }
}

task checkServo() {
  servo[grabber] = 0;

  while(true) {
    getJoystickSettings(joystick);
    if(joystick.joy2_TopHat == 0) {
      servo[grabber] = 224;
    }
    if(joystick.joy2_TopHat == 1) {
      servo[grabber] = 192;
    }
    if(joystick.joy2_TopHat == 2) {
      servo[grabber] = 160;
    }
    if(joystick.joy2_TopHat == 3) {
      servo[grabber] = 128;
    }
    if(joystick.joy2_TopHat == 4) {
      servo[grabber] = 96;
    }
    if(joystick.joy2_TopHat == 5) {
      servo[grabber] = 64;
    }
    if(joystick.joy2_TopHat == 6) {
      servo[grabber] = 32;
    }
    if(joystick.joy2_TopHat == 7) {
      servo[grabber] = 0;
    }
    //An awesome little snippet I came up with to make our servos seem somewhat "continuous"
    if(joy2Btn(4) == 1) {
      servo[grabber] = ServoValue[grabber] + 1;
    } else if (joy2Btn(2) == 1) {
      servo[grabber] = ServoValue[grabber] - 1;
    }
  }
}

task main()
{
  waitForStart();

  StartTask(checkDrive);
  StartTask(checkArm);
  StartTask(checkServo);

  while(1) wait10Msec(1000);
}
