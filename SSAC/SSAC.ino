//MOTOR PINS MUST BE ANALOG
//ANALOG PINS: 3, 5, 6, 9, 10, 11

//front right motor
int motor1pin1 = 5;
int motor1pin2 = 6;

//back left motor
int motor2pin1 = 10;
int motor2pin2 = 11;

/*int front_lightsensor_pin = 10;
int left_lightsensor_pin = 11;
int back_lightsensor_pin = 12;
int right_lightsensor_pin = 13;*/

void setup() {

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);

  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  /*pinMode(front_lightsensor_pin, INPUT);
  pinMode(left_lightsensor_pin, INPUT);
  pinMode(back_lightsensor_pin, INPUT);
  pinMode(right_lightsensor_pin, INPUT);*/
  drive(100);

}

void drive (int power) { //power is a value between 1 - 100

  int analogValue = ((float) power / 100) * 255;

  //analogWrite has value parameter between 0 (always off) and 255 (always on)
  analogWrite(motor1pin1, analogValue);
  digitalWrite(motor1pin2, LOW); //pin 2 to zero volts

  analogWrite(motor2pin1, analogValue);
  digitalWrite(motor2pin2, LOW); //pin 2 to zero volts

}

void reverse (int power) { //power is a value between 1 - 100

  int analogValue = ((float) power / 100) * 255;

  digitalWrite(motor1pin1, LOW); //pin 1 to zero volts
  analogWrite(motor1pin2, analogValue);

  digitalWrite(motor2pin1, LOW); //pin 1 to zero volts
  analogWrite(motor2pin2, analogValue);

}

void left (int power) {

  int analogValue = ((float) power / 100) * 255;

  //front right motor drive
  analogWrite(motor1pin1, analogValue);
  digitalWrite(motor1pin2, LOW);

  //back left motor reverse
  digitalWrite(motor2pin1, LOW);
  analogWrite(motor2pin2, analogValue);

}

void right (int power) {

  int analogValue = ((float) power / 100) * 255;

  //front right motor reverse
  digitalWrite(motor1pin1, LOW); //pin 1 to zero volts
  analogWrite(motor1pin2, analogValue);

  //back left motor drive
  analogWrite(motor2pin1, analogValue);
  digitalWrite(motor2pin2, LOW); //pin 2 to zero volts

}

void stop() {

  //IF THIS DOESN'T WORK, TRY SETTING BOTH PINS TO "HIGH"

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);

}

void loop() {
  //SOME TEST CODE


}
