//Motor shield test for Panicbot
//2 DC motors: working
//servo: working
//ultrasonic sensor: working if the wires don't touch the screw

// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <Servo.h> 
//edited Ultrasonic library to set input to pin 9 to work with motor driver
#include <UltrasonicRangeSensor.h> 

// DC motor on M2
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
// DC hobby servo
Servo servo1;
// Stepper motor on M3+M4 48 steps per revolution
//AF_Stepper stepper(48, 2);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor party!");
  
  // turn on servo
  //servo1.attach(9); //servo input 2 = pin 9
  servo1.attach(10);  //servo input 1 = pin 10
   
  // turn on motor #2
  motor1.setSpeed(200);
  motor1.run(RELEASE);
  motor2.setSpeed(200);
  motor2.run(RELEASE);
}

int i;

// Test the DC motors, ultrasonic sensor and servo ALL AT ONCE!
void loop() {
 // MotorsAndServoTest();
 UltrasonicRangeSensorTest();
 delay(1000);
}

void MotorsAndServoTest(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  for (i=0; i<255; i++) {
    servo1.write(i);
    motor1.setSpeed(i);  
    motor2.setSpeed(i);  
   // stepper.step(1, FORWARD, INTERLEAVE);
    delay(3);
 }
 
  for (i=255; i!=0; i--) {
    servo1.write(i-255);
    motor1.setSpeed(i);  
    motor2.setSpeed(i);  
   // stepper.step(1, BACKWARD, INTERLEAVE);
    delay(3);
 }
 
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  for (i=0; i<255; i++) {
    servo1.write(i);
    motor1.setSpeed(i);  
    motor2.setSpeed(i);  
    delay(3);
   // stepper.step(1, FORWARD, DOUBLE);
 }
 
  for (i=255; i!=0; i--) {
    servo1.write(i-255);
    motor1.setSpeed(i);  
    motor2.setSpeed(i);  
   // stepper.step(1, BACKWARD, DOUBLE);
    delay(3);
 }
}
 void UltrasonicRangeSensorTest(){
  // check distance, if too short, change direction
  int distance = getRange();
  //Serial.println("distance: ");
  Serial.println(distance);
 }
