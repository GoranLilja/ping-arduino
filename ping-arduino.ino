/*
  Ping))) Sensor

  This sketch reads a PING))) ultrasonic rangefinder and returns the distance
  to the closest object in range. To do this, it sends a pulse to the sensor to
  initiate a reading, then listens for a pulse to return. The length of the
  returning pulse is proportional to the distance of the object from the sensor.

  The circuit:
    - +V connection of the PING))) attached to +5V
    - GND connection of the PING))) attached to ground
    - SIG connection of the PING))) attached to digital pin 7

  created 3 Nov 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Ping
*/

// this constant won't change. It's the pin number of the sensor's output:
const int ping = 5;
const int red = 4;
const int yellow = 3;
const int green = 2;

void setup() {
  // initialize serial communication:
  //Serial.begin(19200);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration;
  int inches, cm;

  triggerPing();

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(ping, INPUT);
  duration = pulseIn(ping, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  if (cm < 20) {
    digitalWrite(red, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
  } else if (cm < 40) {
    digitalWrite(red, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, LOW);
  } else if (cm < 100) {
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, HIGH);
  } else {
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
  }

  //Serial.println(cm);
  delay(10);
}

void triggerPing() {
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(ping, OUTPUT);
  digitalWrite(ping, LOW);
  delayMicroseconds(2);
  digitalWrite(ping, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping, LOW);  
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
