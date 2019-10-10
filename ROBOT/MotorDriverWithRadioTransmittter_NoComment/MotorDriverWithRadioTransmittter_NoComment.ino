#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

int speedy = 0; int speedindir = 0;
int angle; 
byte CH1_PIN = 2; int ch1_value;
byte CH3_PIN = 3; int ch3_value;

Servo myServo;  // create a servo object

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1 and M2
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);
  myServo.attach(10); // attaches the servo on pin 9 to the servo object
  pinMode(CH1_PIN, INPUT);
  pinMode(CH3_PIN, INPUT);

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
  // get values
  ch1_value = pulseIn(CH1_PIN, HIGH);   // channel 1: servo
  Serial.print("Channel 1 value is: ");
  Serial.println(ch1_value);
  ch3_value = pulseIn(CH3_PIN, HIGH);   // channel 3: motor

  // steering
  angle = map((ch1_value + 100), 1023, 2003, 20, 154);
  myServo.write(angle);

  // motor drive and speed
  speedy = map(ch3_value, 1000, 2020, 0, 255);

  // conditions
  
  if (speedy > 118 && speedy < 136)   // forward
  {
    motor1->run(FORWARD); motor2->run(BACKWARD);
    motor1->setSpeed(0); motor2->setSpeed(0);
    delay(5);
  }
  
  if (speedy > 135 && speedy < 256)   // forward
  {
    motor1->run(BACKWARD); motor2->run(FORWARD);
    speedindir = map(speedy, 136, 255, 0, 255);
    motor1->setSpeed(speedindir); motor2->setSpeed(speedindir);
    delay(5);
  }
  else if (speedy > 0 && speedy < 119)   // backward
  {
    motor1->run(FORWARD); motor2->run(BACKWARD);
    speedindir = map(speedy, 118, 0, 0, 255);
    motor1->setSpeed(speedindir); motor2->setSpeed(speedindir);
    delay(5);
  }
}
