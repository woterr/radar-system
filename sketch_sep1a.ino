
#include <Servo.h>

Servo myservo;
int pos = 0;

int outputPin = 2;


int triggerPin = 11;
int echoPin = 12;
int servoPin = 5;
int switchPin = 8;

void setup() {

  pinMode(outputPin, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(servoPin);

  Serial.begin(9600);
}



void loop() {
  
  // loop one 
  
  for (pos = 0; pos <= 180; pos += 3) { // goes from 0 degrees to 180 degrees
    // in steps of 3 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position

    int distance_cm = calculateDistance();


    if (distance_cm < 10){
      digitalWrite(outputPin, HIGH);
    } else {
      digitalWrite(outputPin, LOW);
    }


  }

  // loop two (reverse)
  
  for (pos = 180; pos >= 0; pos -= 3) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);

    int distance_cm = calculateDistance(); // distance of the object in cm


    if (distance_cm < 10){
      digitalWrite(outputPin, HIGH);
    } else {
      digitalWrite(outputPin, LOW);
    }
  }
}


int calculateDistance() {
  long duration, cm;


  // sending out pulse
  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);


  cm = microsecondsToCentimeters(duration);                                                                                                                                                      


  Serial.print("Distance: ");
  Serial.println(cm);
  
  return cm;
}

long microsecondsToCentimeters(long microseconds) {

  // divide by two because ray has to travel to the object and back
  
  return microseconds / 29 / 2;
}
