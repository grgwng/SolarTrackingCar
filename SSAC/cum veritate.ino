//MOTOR PINS MUST BE ANALOG (for speed control)
//ANALOG PINS: 3, 5, 6, 9, 10, 11

#define CLIPPINGDIST 60
#define LIGHTEPSILON 5
//#define EXCLIPPINGDIST 30

#define READINGNUM 5

int stateCounter = 4;

int backmotorpin1 = 10; //power motor
int backmotorpin2 = 11;

int frontmotorpin1 = 6; //steering motor
int frontmotorpin2 = 7;
// int turningDistance = 30; //minimum turning distance from wall (cm)

//front ultrasonic sensor
int sensor1vcc = 2;
int sensor1trig = 3;
int sensor1echo = 4;
int sensor1ground = 5;

//front light sensor
int frontLightSensorPower = 8;
int frontLightSensorAnalog = A5;

//back light sensor
int backLightSensorPower = 9;
int backLightSensorAnalog = A2;

//top light sensor
int topLightSensorPower = 13;
int topLightSensorAnalog = A0;

//misc.
int currDistance = 0;
int pastReading = 100;

int count1182 = 0;
int state = 0;
int lightState = 0;

void setup() {

  Serial.begin(9600);

  //motors
  pinMode(backmotorpin1, OUTPUT);
  pinMode(backmotorpin2, OUTPUT);
  pinMode(frontmotorpin1, OUTPUT);
  pinMode(frontmotorpin2, OUTPUT);

  //front ultrasonic sensor
  pinMode(sensor1trig, OUTPUT);
  pinMode(sensor1echo, INPUT);
  pinMode(sensor1vcc, OUTPUT); //power pins
  pinMode(sensor1ground, OUTPUT);
  digitalWrite(sensor1vcc, HIGH);
  digitalWrite(sensor1ground, LOW);

  //light sensors
  pinMode(frontLightSensorPower, OUTPUT);
  digitalWrite(frontLightSensorPower, HIGH);
  pinMode(backLightSensorPower, OUTPUT);
  digitalWrite(backLightSensorPower, HIGH);
  pinMode(topLightSensorPower, OUTPUT);
  digitalWrite(topLightSensorPower, HIGH);

}

void loop() {

  delay(200);

  int currentDistance = distanceFront();
  int lightPos = getLightPos();

  if (currentDistance > CLIPPINGDIST) { //NOTHING IN FRONT OF US -> GO FORWARD
    
    stopTurn();

    if (senseLightTop() >= 80) { //light is on top of the rover
          
      Serial.println("STAY");
      stateChecker();

    } else if (lightPos == 1) {
      Serial.println("FORWARD");
      drive(100);
      state = 1; //driving forward now

    } else if(lightPos == -1) {
      Serial.println("BACKWARD");
      reverse();
      state = -1; //reversing now

    } else {

      stateChecker();

      for (int i = 0; i < 10; i++) { //checks for extraneous readings

        if (getLightPos() != 0){ //If light is no longer equal, exit out of loop
          return;
        }
        Serial.println("CHECK");
        delay(300);

      }
        Serial.println("TURN AROUND");
      //TURN AROUND
        reverse();
        delay(500);
        right();
        delay(1500);
    
        brakeReverse();
        delay(200);

        //TURN LEFT
        left();
        delay(20);

        drive(100);
        delay(1000);
        brakeForward();
        delay(200);

        stop();

    }

  } else { //WITHIN CLIPPING DISTANCE

    stateChecker();

    //REVERSE TO THE RIGHT
    reverse();
    delay(500);
    right();
    delay(1500);
    
    // delay(20);

    // reverse();
    // delay(800);
    brakeReverse();

    delay(200);

    //TURN LEFT
    left();
    delay(20);

    drive(100);
    delay(1000);
    brakeForward();
    delay(200);

  }

  //Serial.print("State: ");
  //Serial.println(state);

}

void stateChecker() {
  if (state == 1) { //IF WAS GOING FORWARD, CANCEL MOMENTUM

    brakeForward();
    state = 0; //we are stationary

    delay(1000);

  }

  else if (state == -1) { //IF WAS GOING BACKWARDS, CANCEL MOMENTUM

    brakeReverse();
    state = 0; //we are stationary

    delay(1000);

  }

  else {

    stop();
    state = 0;

    delay(1000);

  }
}

int getLightPos(){
  int front = senseLightFront();
  int back = senseLightBack();

  if(front - back > LIGHTEPSILON){
    return 1;
  }else if(front - back < -LIGHTEPSILON){
    return -1;
  }else{
    return 0;
  }
}

int senseLightFront() {

  int value = analogRead(frontLightSensorAnalog);
  Serial.print("Front light: ");
  Serial.println(value);
  return value;

}

int senseLightBack() {

  int value = analogRead(backLightSensorAnalog);
  Serial.print("Back light: ");
  Serial.println(value);
  return value;
  
}

int senseLightTop() {

  int value = analogRead(topLightSensorAnalog);
  Serial.print("Top light: ");
  Serial.println(value);
  return value;

}

void brakeForward(){
    reverse();
    delay(100);
    stop();
    delay(200);
    //delay(500);
}

void brakeReverse(){
    drive(100);
    delay(100);
    stop();
    delay(200);
    //delay(500);
}             

void drive (int power) { //power takes value between 1-100 (inclusive)

  if (power > 100 || power < 1) {
    Serial.println("power out of bounds in DRIVE");
    abort();
  }

  int analogValue = 255 * (power / (float)100.0);

  analogWrite(backmotorpin1, analogValue);
  digitalWrite(backmotorpin2, LOW);

}

void reverse () {

  digitalWrite(backmotorpin1, LOW);
  digitalWrite(backmotorpin2, HIGH);

}

void stop() { //STOP BACK MOTOR WHEELS AND STOP TURNING

  digitalWrite(backmotorpin1, LOW);
  digitalWrite(backmotorpin2, LOW);

  digitalWrite(frontmotorpin1, LOW);
  digitalWrite(frontmotorpin2, LOW);

}

void left () {

  digitalWrite(frontmotorpin1, HIGH);
  digitalWrite(frontmotorpin2, LOW);

}

void right () {

  digitalWrite(frontmotorpin1, LOW);
  digitalWrite(frontmotorpin2, HIGH);

}

void stopTurn() {

  digitalWrite(frontmotorpin1, LOW);
  digitalWrite(frontmotorpin2, LOW);

}

//returns distance to object in cm
int distanceFront () {
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

// For the sensor reading fluctuation (1177)
int distanceFiltered(){

  int x = distanceFront();

  if(x != 1182 && x != 1183){
    count1182 = 0;
    pastReading = x;
    return pastReading;

  }else{
    if(count1182 >= 10){
      count1182++;
      return 1182;
    }else{
      count1182++;
      return 0;
    }
    

  }

  if(x == 1182 || x == 1183){
    return pastReading;

  } else {
    pastReading = x;
    return pastReading;
  }
}