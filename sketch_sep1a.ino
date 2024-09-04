
#include <Servo.h>

Servo myservo;
int pos = 0;

int outputPin = 2;


int triggerPin = 11;
int echoPin = 12;
int servoPin = 5;
int switchPin = 8;

void setup() {
  // put your setup code here, ttriggerPino run once:
  // pinMode(sensorPin, INPUT);
  pinMode(outputPin, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(servoPin);

  // digitalWrite(outputPin, LOW);

  Serial.begin(9600);
}



void loop() {
  for (pos = 0; pos <= 180; pos += 3) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position

    int distance_cm = calculateDistance();


    if (distance_cm < 10){
      digitalWrite(outputPin, HIGH);
    } else {
      digitalWrite(outputPin, LOW);
    }


  }
  for (pos = 180; pos >= 0; pos -= 3) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);

    int distance_cm = calculateDistance();


    if (distance_cm < 10){
      digitalWrite(outputPin, HIGH);
    } else {
      digitalWrite(outputPin, LOW);
    }
  }
}


int calculateDistance() {
  long duration, cm;

  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);


  cm = microsecondsToCentimeters(duration);                                                                                                                                                      


  Serial.print("Distance: ");
  Serial.println(cm);

  // delay(100);

  //  if (cm < 5){
  //   digitalWrite(outputPin, HIGH);
  //  } else {
  //   digitalWrite(outputPin, LOW);
  //  }

  return cm;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
