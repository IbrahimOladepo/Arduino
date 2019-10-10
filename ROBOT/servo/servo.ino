#include <Servo.h>

Servo myServo;

void setup() 
{
  Serial.begin(9600);
  myServo.attach(9);
}

void loop()
{
  //int potValue = analogRead(A0);

  //int angleValue = map(380, 0, 1023, 0, 180);
  myServo.write(89);
  //Serial.println(potValue);
  //Serial.println(angleValue);
  delay(500);
}
