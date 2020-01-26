/*
 * This is loosely based on the autonomous car project 
 * found here: https://www.instructables.com/id/Arduino-Self-Driving-Car/
 * For extra panic, add a flashing red light and siren noises to the top so
 * that when there's an emergency, this will speed around at random 
 * attracting attention and remove the need for managers to perform this job.
 */

#include <AFMotor.h>
#include <Servo.h> 
//edited Ultrasonic library to set input to pin 9 to work with motor driver
#include <UltrasonicRangeSensor.h> 

// DC motor
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
// DC servo
Servo servo1;
int counter;
int distance, leftDistance, rightDistance;

void setup() {
  Serial.begin(9600); 
  servo1.attach(10);
  servo1.write(90);
  
  motor1.setSpeed(200);
  motor1.run(RELEASE);
  motor2.setSpeed(200);
  motor2.run(RELEASE);
}

void loop() {
  // check distance - if too short, change direction
  distance = getRange();
CheckDistance(); //outputs distance to serial monitor

 if(distance <20){
  Serial.println("change direction");
  changePath();
 }
// else{
//  Serial.println("go forward");
// }

//for extra randomness, if it's gone in a straight path for too long, just change again.
//changePath function resets the counter
if(counter > 1000){
  randomDirection();
}
counter = counter +1;
 
}//end loop

//===DECISIONS==========================================================
void lookAndTurn(){   
  // find the longest distance
    servo1.write(36);  // check distance to the right
    delay(500);
    rightDistance = getRange(); //set right distance
    delay(200);
    servo1.write(144);  // check distace to the left
    delay(500);
    leftDistance = getRange(); //set left distance
    delay(200);
    servo1.write(90); //return to center
    delay(200);
    
  if (leftDistance>rightDistance) //if left has more space
  {
    turnLeft();
  }
  else if (rightDistance>leftDistance) //if right has more space
  {
    turnRight();
  }
   else //if they are equally obstructed
  {
    halfTurn();
  }
}

void randomDirection(){
  int r = random(4);
Serial.print("Random!! ");
Serial.println(r);
  if(r== 0){
    turnRight();
  }
  else if (r == 1){
    turnLeft();
  }
  else if(r==2){
    halfTurn();
  }
  else{
    Shake();
    halfTurn();
  }
  moveForward();
}

//===MOVEMENT============================================================
void changePath(){
  moveStop();
  moveBackward();
  lookAndTurn();
  moveForward();
  counter = 0;
}

void moveStop(){
    motor1.setSpeed(0);  
    motor2.setSpeed(0); 
    delay(500);
}

void moveForward(){
    motor1.run(FORWARD);
  motor2.run(FORWARD);
    motor1.setSpeed(200);  
    motor2.setSpeed(200); 
}

void moveBackward(){
  //go backwards 2 seconds and stop
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor1.setSpeed(200);  
    motor2.setSpeed(200); 
    delay(2000);
    moveStop();
    motor1.run(FORWARD);
    motor2.run(FORWARD);
}

void turnRight(){
      motor1.setSpeed(50);  
    motor2.setSpeed(200); 
  delay(3000);
}

void turnLeft(){
      motor1.setSpeed(200);  
    motor2.setSpeed(50); 
  delay(3000);
}

void halfTurn(){
      motor1.setSpeed(50);  
    motor2.setSpeed(200); 
  delay(6000);
}

//=====================================================================
void CheckDistance(){
  //outputs distance to serial monitor
  Serial.print("counter: ");
  Serial.println(counter);
  Serial.print("distance: ");
  Serial.println(distance);
}

void Shake(){
  //"shakes" its head - moves servo back and forth.  Just looks funny
   moveStop();
        servo1.write(20);  // check distance to the right
    delay(200);
      servo1.write(160);  // check distance to the right
    delay(300);
      servo1.write(20);  // check distance to the right
    delay(300);
      servo1.write(90);  // check distance to the right
    delay(200);
}
