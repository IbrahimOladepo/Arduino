#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define speedy 60 

// defines pins numbers
const int trigPin = 2;
const int echoPin = 3;

// defines variables
long duration;
int distance;

int angle;   // variable to hold the angle for the servo motor
int x = 100;
int location = 500;
int y;
int turn = 0;

Servo myServo;  // create a servo object

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1 and M2
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);
  myServo.attach(10); // attaches the servo on pin 9 to the servo object
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  // Set the speed to start, from 0 (off) to 255 (max speed)
  motor1->setSpeed(speedy);
  motor1->run(FORWARD);
  // turn on motor
  motor1->run(RELEASE);

  motor2->setSpeed(speedy);
  motor2->run(BACKWARD);
  // turn on motor
  motor2->run(RELEASE);

  angle = map(500, 0, 1023, 0, 179);
  myServo.write(angle);
}

void loop() {
  if (turn == 0)
  {
    right();
    delay(2000);
    turn = turn + 1;
  }
  else
  {
    left();
    delay(2000);
    turn = turn - 1;
  }
  
  
  x = 14;
  myServo.write(x);
  delay(1000);
  
  while(x < 180)
  {
    myServo.write(x);
    x = x + 27.5;
    delay(1000);
    y = dist();
  }
  
  stopper();
  delay(1000);
}

int dist() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration * 0.034 / 2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}

void forward()
{
  motor1->run(FORWARD);
  motor2->run(BACKWARD);
  motor1->setSpeed(speedy); 
  motor2->setSpeed(speedy);
}

void backward()
{
  motor1->run(BACKWARD);
  motor2->run(FORWARD);
  motor1->setSpeed(speedy); 
  motor2->setSpeed(speedy);
}

void right()
{
  motor1->run(FORWARD);
  motor2->run(FORWARD);
  motor1->setSpeed(speedy); 
  motor2->setSpeed(speedy);
}

void left()
{
  motor1->run(BACKWARD);
  motor2->run(BACKWARD);
  motor1->setSpeed(speedy); 
  motor2->setSpeed(speedy);
}

void stopper()
{
  //motor1->run(BACKWARD);
  //motor2->run(BACKWARD);
  motor1->setSpeed(0); 
  motor2->setSpeed(0);
}
