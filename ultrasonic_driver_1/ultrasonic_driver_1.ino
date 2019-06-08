/*
 * This is a modified version of the autonomous car project 
 * found here: https://www.instructables.com/id/Arduino-Self-Driving-Car/
 * The idea is to add a flashing red light and siren to the top so
 * that when there's an emergency, this will speed around at random 
 * making noise and remove the need for managers to perform this job.
 */

#include <UltrasonicRangeSensor.h>
#include <Servo.h>

//ultrasonic sensor library sets it to pin 7

//motors
int pwm_a = 3;  //PWM control for motor outputs 1 and 2 
int pwm_b = 9;  //PWM control for motor outputs 3 and 4 
int dir_a = 2;  //direction control for motor outputs 1 and 2 
int dir_b = 8;  //direction control for motor outputs 3 and 4 

int counter = 0;
int leftDistance, rightDistance;

Servo servo1;

void setup() {
  
  Serial.begin(9600);
  


randomSeed(analogRead(0));
  //motors
  //Set control pins to be outputs
  pinMode(pwm_a, OUTPUT);  
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);

//set direction to Forward
      digitalWrite(dir_a, LOW); 
  digitalWrite(dir_b, LOW); 

 servo1.attach(6);
 servo1.write(90);
 delay(1000);
}

void loop() {
  
  // check distance, if too short, change direction
  Serial.print("counter: ");
  Serial.println(counter);
  int distance = getRange();
  Serial.print("distance");
  Serial.println(distance);
  
  servo1.write(90);
  delay(200);
  
  if(distance < 20){
    Serial.println("change");
    changePath();

  }
  else{
    Serial.println("forward");
    moveForward();
  }

//for extra randomness, if it's gone in a straight path for too long, just change again.
//change path resets the counter
if(counter > 800){
  randomDirection();
}
counter = counter +1;
}

//---------------------------------------------------
//distance
void changePath(){
moveStop();
moveBack();

//randomDirection();
compareDistance();

  moveForward();
  counter = 0;
}

//----------------------------------------------------
//decisions
void randomDirection(){
  //the following doesn't do anything - it just looks funny
      servo1.write(20);  // check distance to the right
    delay(200);
      servo1.write(160);  // check distance to the right
    delay(300);
      servo1.write(20);  // check distance to the right
    delay(300);
      servo1.write(90);  // check distance to the right
    delay(200);

int r = random(3);
Serial.print("random ");
Serial.println(r);
  if(r== 0){
    turnRight();
    Serial.println("right");
  }
  else if (r == 1){
    turnLeft();
    Serial.println("left");
  }
  else{
    halfTurn();
    Serial.println("half turn");
  }
}

void compareDistance()   // find the longest distance
{
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
    
  if (leftDistance>rightDistance) //if left is less obstructed 
  {
    turnLeft();
  }
  else if (rightDistance>leftDistance) //if right is less obstructed
  {
    turnRight();
  }
   else //if they are equally obstructed
  {
    halfTurn();
  }
}




//-----------------------------------------------------
//movement
void moveStop(){
  analogWrite(pwm_a, 0);  
  analogWrite(pwm_b, 0);
  delay(200);
}

void moveBack(){
  //set direction to backward
  digitalWrite(dir_a, HIGH); 
  digitalWrite(dir_b, HIGH); 

  analogWrite(pwm_a, 245);  
  analogWrite(pwm_b, 250);
  delay(2000); // hopefully 2 sec backwards is about right

  moveStop();
  //change back to forward
  digitalWrite(dir_a, LOW); 
  digitalWrite(dir_b, LOW); 
}

void moveForward(){
   analogWrite(pwm_a, 247);  
  analogWrite(pwm_b, 250);

}

void turnRight(){
   analogWrite(pwm_a, 150);  
  analogWrite(pwm_b, 250);
  delay(3000);
}

void turnLeft(){
    analogWrite(pwm_a, 250);  
  analogWrite(pwm_b, 150);
 delay(3000);
}

void halfTurn(){
     analogWrite(pwm_a, 150);  
  analogWrite(pwm_b, 250);
 delay(6000);
}
