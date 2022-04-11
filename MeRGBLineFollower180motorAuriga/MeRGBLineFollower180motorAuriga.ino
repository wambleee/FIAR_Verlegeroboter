/**
 * @file    MeRGBLineFollower180motorAuriga.ino
 * @author  Khalid Benmahria, Mike Schmitt , Matthias Lammert
 * @version V1.0
 * @date    01.2022
 * @brief   Programm for Linefollow Robot that measrues height of pipe
**/

#include "MeRGBLineFollower.h"
#include <AFMotor.h>

// Initalize LineFollower
MeRGBLineFollower RGBLineFollower(A4, A5, 0);

// Initialize motors on the motor shield
AF_DCMotor motor1(3);
AF_DCMotor motor2(4);

// Initialize Pin for Piezospeaker
int pinTone = A2;

// Initialize Lichtschranke
int pinLightBarrier = A0;
int valueLightBarrier;

// Command that is send over bluetooth
char command = 'x';

// Save last command to later reset +,- and ? command after to the command before
// Prevents running these commands in every loop
char lastCommand = 'x';

// Counter for checking the driving situation(LineFollower)
int criticaldrive = 0;

// linefollower Offset to the right (positive values) or left (negative values)
double kp = 0.1; // old=0.3, 0.1 (best), 0.05
int turnoffset;
int lastturnoffset;

// Initialize threshold for turnoffset when the robot should turn left or right (+/-)
// The output is taken as the product of the line following sensitivity Kp and the analog value resulted from fusion algorithm of the 4 sensors, ranging from -512 to 512
// Threshold also determines when robot makes a hard turn 
int turnThreshold = 512*kp*0.6;


// Initialize variables for speed
int baseSpeed = 90;
int minSpeed = 50;
int maxSpeed = 125;
int turnSpeed = 210; // last=220

void setup()
{
  // Start Serial Input and Output (for bluetooth)
  Serial.begin(9600);

  // Start Line Follower and set it's sensitivity
  RGBLineFollower.begin();
  RGBLineFollower.setKp(kp);

  // Set Motor Speed to default value (does not start motors)
  motor1.setSpeed(baseSpeed);
  motor2.setSpeed(baseSpeed);
}

void loop()
{
  get_BTcommand();
  valueLightBarrier = digitalRead(pinLightBarrier);

  // if Light Barrier is triggered set command to x to stop robot
  // send message via bluetooth and make sound
  if (valueLightBarrier == 1) {
    command = 'x';
    Serial.println();
    Serial.println("Pipe to high! Check Pipe and continue");
    Serial.println("Robot stops moving");
    tone(pinTone, 1000, 1000);
  }
  else if (criticaldrive > 7)
  {
    command = 'x';
    Serial.println();
    Serial.println("Robot has arrived a critical driving situation");
    Serial.println("Robot stops moving");
  }
  
  // Run bluetooth command, that was send
  // Stop robot (in case lightbarrier is triggered opr bluetooth command  'x' was send)
  if (command == 'x') {
    mStop();
    //return;
  }
  else {
  // Increase Speed for '+' command
  if (command == '+') {
    increaseSpeed(1);
  }
  // Decrease Speed for '-' command
  else if (command == '-') {
    decreaseSpeed(1);
  }
  // Print Help (
  else if (command == '?' or command=='h') {
    printHelp();
    command = lastCommand;
  }
  
  // Turn off Alarm sound
  noTone(pinTone);

  
  // Read Linefollower offset
  RGBLineFollower.loop();

  // Set lastturnoffset (used to find cable again in sharp corners)
  if (turnoffset != 0) {
    lastturnoffset = turnoffset;
  }
  
  turnoffset = RGBLineFollower.getPositionOffset();
  
  if (turnoffset > (turnThreshold * (-1)) and turnoffset < 0) {
    turnLeft();
  }
  // Move to right for lower offsets
  else if (turnoffset < turnThreshold and turnoffset > 0) {
    turnRight();
  }
  // Hard turns for high offsets from 0
  else if (turnoffset >= turnThreshold) {
    hardTurnRight();
  }
  else if (turnoffset <= turnThreshold * (-1)) {
    hardTurnLeft();
  }
  else {
      // Rotate robot in last known direction
      if (lastturnoffset > 0) {
          hardTurnRight();
      }
      else {
          hardTurnLeft();
      }    
  }

  // Print turnOffset of Linefollower
  Serial.println("TurnOffset= ");
  Serial.print(turnoffset);
  }
}


// Robot turns left by using the higher turnSpeed on one motor
void turnLeft() {
  Serial.println();
  Serial.println("Turn Left");
  motor1.run(RELEASE);
  motor2.run(FORWARD);
  motor1.setSpeed(baseSpeed);
  motor2.setSpeed(turnSpeed);
  criticaldrive = 0;
}

// Robot turns right by using the higher turnSpeed on one motor
void turnRight() {
  Serial.println();
  Serial.println("Turn Right");
  motor1.run(FORWARD);
  motor2.run(RELEASE);
  motor1.setSpeed(turnSpeed);
  motor2.setSpeed(baseSpeed);
  criticaldrive = 0;
}

// Turn in place (right)
void hardTurnRight() {
  Serial.println();
  Serial.println("Hard Turn Right");
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  criticaldrive = criticaldrive + 1;
}

// Trun in place (left)
void hardTurnLeft() {
  Serial.println();
  Serial.println("Hard Turn Left");
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  criticaldrive = criticaldrive + 1;
}

// Robot turns left by using same baseSpeed for both motors
void forward() {
  Serial.println();
  Serial.println("Move forward");
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor1.setSpeed(baseSpeed);
  motor2.setSpeed(baseSpeed);
  criticaldrive = 0;
}

// Stop motors of the robot
void mStop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  criticaldrive = 0;
}

// Print help (commands that can be used to control robot)
void printHelp() {
  Serial.println("+ = Increase Speed");
  Serial.println("- = Decrease Speed");
  Serial.println("?, h = Help");
  Serial.println("x = Stop Motors (Used for Alarm as well)");
  Serial.println("any other key = Continue after Alarm/Stop");
}

// Get the bluetooth command if one was send
void get_BTcommand() {
  // Read Serial signal
  if (Serial.available()) {
    // Set lastCommand 
    lastCommand = command;
    command = Serial.read();
    command = toLowerCase(command);
  }
}

void decreaseSpeed(int reduce) {
  if (baseSpeed > minSpeed and turnSpeed > minSpeed) {
    // Increase Speed
    baseSpeed -= reduce;
    turnSpeed -= reduce;

    // Apply to motors
    motor1.setSpeed(baseSpeed);
    motor2.setSpeed(baseSpeed);
    Serial.print("Speed decreased to ");
    Serial.println(baseSpeed);
  }
  // Print response
  else {
    Serial.println("Min Speed reached!");
  }
  // Reset command to lastCommand (prevent running it a second time)
  command = lastCommand;
}

// Increase turn and baseSpeed and apply it to the motors
void increaseSpeed(int increase) {
  if (baseSpeed < maxSpeed and turnSpeed < 256) {
    // Increase Speed
    baseSpeed += increase;
    turnSpeed += increase;

    // Apply to motors
    motor1.setSpeed(baseSpeed);
    motor2.setSpeed(baseSpeed);

    // Print response
    Serial.print("Speed increased to ");
    Serial.println(baseSpeed);
  }
  else {
    Serial.println("Max Speed reached!");
  }
  
  // Reset command to lastCommand (prevent running it a second time)
  command = lastCommand;
}
