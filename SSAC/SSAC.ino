#include <Stepper.h>

//MOTOR PINS MUST BE ANALOG
//ANALOG PINS: 3, 5, 6, 9, 10, 11

//left stepper motor
int motor1pin1 = 10;
int motor1pin2 = 11;
int motor1pin3 = 12;
int motor1pin4 = 13;

Stepper myStepper(200, motor1pin1, motor1pin2, motor1pin3, motor1pin4);

//front ultrasonic sensor
int sensor1vcc = 1;
int sensor1trig = 2;
int sensor1echo = 3;
int sensor1ground = 4;

void setup() {
  myStepper.setSpeed(60);
  Serial.begin(9600);

  //front right motor
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);

  //front ultrasonic sensor
  pinMode(sensor1trig, OUTPUT);
  pinMode(sensor1echo, INPUT);
  pinMode(sensor1vcc, OUTPUT); //power pins
  pinMode(sensor1ground, OUTPUT);
  digitalWrite(sensor1vcc, HIGH);
  digitalWrite(sensor1ground, LOW);

}

void drive () {

  //2000 steps is a full revolution
  myStepper.step(2000);

}

void reverse (int power) { //power is a value between 1 - 100

}

void left (int power) {

}

void right (int power) {

}

void stop() {


}

int distanceFront () {

  //NOTE: When object is too close or it doesn't detect anything,
  //this function returns 1177 (by experimentation)

  int distance = 0;
  long duration = 0;

  // Clears the trigPin condition
  digitalWrite(sensor1trig, LOW);
  delayMicroseconds(2);

  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(sensor1trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor1trig, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(sensor1echo, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (to and back)

  //FOR DEBUGGING PURPOSES
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;

}

void loop() {
  //SOME TEST CODE

  drive();
  delay(1000);

}
