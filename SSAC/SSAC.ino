//MOTOR PINS MUST BE ANALOG (for speed control)
//ANALOG PINS: 3, 5, 6, 9, 10, 11

#define READINGNUM 5

int backmotorpin1 = 10; //power motor
int backmotorpin2 = 11;

int frontmotorpin1 = 12; //steering motor
int frontmotorpin2 = 13;
int turningDistance = 30; //minimum turning distance from wall (cm)

//front ultrasonic sensor
int sensor1vcc = 1;
int sensor1trig = 2;
int sensor1echo = 3;
int sensor1ground = 4;

int currDistance = 0;
int distReadings[READINGNUM] = {15, 15, 15, 15, 15};
int pastReading = 0;

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

  

}

void drive (int power) { //power takes value between 1-100 (inclusive)

  if (power > 100 && power < 1) {
    Serial.println("power out of bounds in DRIVE");
    abort();
  }

  int analogValue = 255 * ((float) 100.0 / power);

  analogWrite(backmotorpin1, analogValue);
  digitalWrite(backmotorpin2, LOW);

}

void reverse (int power) {

  if (power > 100 && power < 1) {
    Serial.println("power out of bounds in REVERSE");
    abort();
  }

  int analogValue = 255 * ((float) 100.0 / power);

  digitalWrite(backmotorpin1, LOW);
  analogWrite(backmotorpin2, analogValue);

}

void stop() {

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

// For the sensor reading fluctuation (1177)
int distanceFiltered(){

  int x = distanceFront();
  if(x > 1000){
    return pastReading;

  }else{
    pastReading = x;
    return pastReading;

  }

/*
  //Calculate average over 5 most recent scans
  int dist = distanceFront();

  int sum = 0;
  for(int i = 0; i <= READINGNUM-2; i++){
    distReadings[i] = distReadings[i+1];
    sum+=distReadings[i];
  }
  distReadings[READINGNUM-1] = dist;
  sum+= dist;

  sum /= READINGNUM;
  
  Serial.print("Avg Distance: ");
  Serial.print(sum);
  Serial.println(" cm");
  */

  // return sum;

}



void loop() {

  //we must implement checks for false readings (i.e. taking the average reading over x milliseconds)

   

  /*
  if(distanceFiltered() < 5){ //VERY CLOSE
    stopTurn();
    reverse(50);

  }else if(distanceFiltered() < 15){ //CLOSE
    left();
    drive(10);
    
  }else{ //FAR
    stopTurn();
    drive(50);
  }
  */









}
