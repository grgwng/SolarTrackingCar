int left_motor_pin = 8;
int right_motor_pin = 9;

int front_lightsensor_pin = 10;
int left_lightsensor_pin = 11;
int back_lightsensor_pin = 12;
int right_lightsensor_pin = 13;

//PINS
/*
Left Motor: 8
Right Motor: 9
Front light sensor: 10
Left light sensor: 11
Back light sensor: 12
Right light sensor: 13
*/

//METHODS
//pinMode(pin, mode) 
//mode: INPUT, OUTPUT, or INPUT_PULLUP

//digitalWrite(pin, value)
//value: HIGH or LOW.

//4 x sun sensors
//1 x depth sensor

//motor (L) pin D13
//motor (R) pin D2

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(left_motor_pin, OUTPUT);
  pinMode(right_motor_pin, OUTPUT);
  pinMode(front_lightsensor_pin, INPUT);
  pinMode(left_lightsensor_pin, INPUT);
  pinMode(back_lightsensor_pin, INPUT);
  pinMode(right_lightsensor_pin, INPUT);
  

}

void forward(){
  Serial.println("Forward");
  digitalWrite(left_motor_pin, HIGH);
  digitalWrite(right_motor_pin, HIGH);
}

void right(){
  Serial.println("Right");
  digitalWrite(left_motor_pin, HIGH);
  digitalWrite(right_motor_pin, LOW);
}

void left(){
  Serial.println("Left");
  digitalWrite(left_motor_pin, LOW);
  digitalWrite(right_motor_pin, HIGH);
}

void stop(){
  Serial.println("Stop");
  digitalWrite(left_motor_pin, LOW);
  digitalWrite(right_motor_pin, LOW);
}



void loop() {
  // put your main code here, to run repeatedly:

}
