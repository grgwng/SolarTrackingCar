//MOTOR PINS MUST BE ANALOG (for speed control)
//ANALOG PINS: 3, 5, 6, 9, 10, 11

int backmotorpin1 = 10;
int backmotorpin2 = 11;

int frontmotorpin1 = 12;
int frontmotorpin2 = 13;

//front ultrasonic sensor
int sensor1vcc = 1;
int sensor1trig = 2;
int sensor1echo = 3;
int sensor1ground = 4;

int currDistance = 0;
int distReadings[5] = {15, 15, 15, 15, 15};

void setup() {

  Serial.begin(9600);

  //front ultrasonic sensor
  pinMode(sensor1trig, OUTPUT);
  pinMode(sensor1echo, INPUT);
  pinMode(sensor1vcc, OUTPUT); //power pins
  pinMode(sensor1ground, OUTPUT);
  digitalWrite(sensor1vcc, HIGH);
  digitalWrite(sensor1ground, LOW);

  

}

void drive (int power) { //implement speed control with analog pins?

}

void reverse (int power) {

}

void left () {

}

void right () {

}

void stop() {


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


int distanceFiltered(){

  //Calculate average over 5 most recent scans
  int dist = distanceFront();

  int sum = 0;
  for(int i = 0; i <= 3; i++){
    distReadings[i] = distReadings[i+1];
    sum+=distReadings[i];
  }
  distReadings[5] = dist;
  sum+= dist;

  return sum;

}



void loop() {

  //we must implement checks for false readings (i.e. taking the average reading over x milliseconds)

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









}
