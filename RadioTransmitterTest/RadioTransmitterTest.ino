#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int val;    // variable to read the value from the analog pin
int ch1,ch2;
int speedy = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  myservo.attach(9); 

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  ch1 = pulseIn(2, HIGH, 25000) / 25;     // motot
  ch2 = pulseIn(3, HIGH, 25000) / 50;     // steering

  // check
  if (ch1 < 40){
    ch1 = 40;
  }
  else if (ch1 > 80){
    ch1 = 80;
  }

  val = map(ch2, 20, 40, 65, 115);
  myservo.write(val);  

  speedy = map(ch1, 40, 80, 0, 255);

  Serial.print("Channel 1: ");    // motor
  Serial.println(ch1);

  Serial.print("Speedy: ");       // speed
  Serial.println(speedy);
  
  Serial.print("Channel 2: ");    // steering
  Serial.println(ch2);

  Serial.print("Angle: ");        // angle
  Serial.println(val);

  Serial.println("");
  Serial.println("");

  delay(1000);
}
