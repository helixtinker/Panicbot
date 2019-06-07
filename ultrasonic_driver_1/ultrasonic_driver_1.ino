#include <UltrasonicRangeSensor.h>

/*
 * This is a modified version of the autonomous car project 
 * found here: https://www.instructables.com/id/Arduino-Self-Driving-Car/
 * The idea is to add a flashing red light and siren to the top so
 * that when there's an emergency, this will speed around at random 
 * making noise and remove the need for managers to perform this job.
 */


//motors
int pwm_a = 3;  //PWM control for motor outputs 1 and 2 
int pwm_b = 9;  //PWM control for motor outputs 3 and 4 
int dir_a = 2;  //direction control for motor outputs 1 and 2 
int dir_b = 8;  //direction control for motor outputs 3 and 4 

int counter = 0;

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
      digitalWrite(dir_a, HIGH); 
  digitalWrite(dir_b, HIGH); 
}

void loop() {
  // check distance, if too short, change direction
  Serial.print("counter: ");
  Serial.println(counter);
  int distance = getRange();
  Serial.print("distance");
  Serial.println(distance);
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
if(counter > 1000){
  changePath();
}
counter = counter +1;
}

//---------------------------------------------------
//distance
void changePath(){
moveStop();
moveBack();
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
  moveForward();
  counter = 0;
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
  digitalWrite(dir_a, LOW); 
  digitalWrite(dir_b, LOW); 

  analogWrite(pwm_a, 245);  
  analogWrite(pwm_b, 250);
  delay(2000); // hopefully 2 sec backwards is about right

  moveStop();
  //change back to forward
  digitalWrite(dir_a, HIGH); 
  digitalWrite(dir_b, HIGH); 
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
