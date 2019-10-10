#include <IRremote.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define speedy 250

int RECV_PIN = 7;
int x;

IRrecv irrecv(RECV_PIN);
decode_results results;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1 and M2
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

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
}

void loop() {
  if (irrecv.decode(&results)) 
  {
    // get key being pressed
    x = results.value;
    Serial.println(x);

    // moving conditions
    if (x == 14535)   // forward
    {
      motor1->run(FORWARD);
      motor2->run(BACKWARD);
      motor1->setSpeed(speedy); 
      motor2->setSpeed(speedy);
      delay(200);
    }
    else if (x == 6375)   // backward
    {
      motor1->run(BACKWARD);
      motor2->run(FORWARD);
      motor1->setSpeed(speedy); 
      motor2->setSpeed(speedy);
      delay(200);
    }
    else if (x == -4081)   // right
    {
      motor1->run(FORWARD);
      motor2->run(FORWARD);
      motor1->setSpeed(speedy); 
      motor2->setSpeed(speedy);
      delay(200);
    }
    else if (x == -10201)   // left
    {
      motor1->run(BACKWARD);
      motor2->run(BACKWARD);
      motor1->setSpeed(speedy); 
      motor2->setSpeed(speedy);
      delay(200);
    }
    else if (x == -20401)   // stop
    {
      motor1->run(BACKWARD);
      motor2->run(FORWARD);
      motor1->setSpeed(0); 
      motor2->setSpeed(0);
      delay(200);
    }
    
    // resume receiver
    irrecv.resume(); 
  }
}
