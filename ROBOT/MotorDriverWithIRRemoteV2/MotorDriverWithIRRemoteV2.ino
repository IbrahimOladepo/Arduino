#include <IRremote.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define speedy 200

int angle;   // variable to hold the angle for the servo motor
int RECV_PIN = 7;   // receiver pin
int x;
int location = 380;

Servo myServo;  // create a servo object

IRrecv irrecv(RECV_PIN);
decode_results results;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1 and M2
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);
  myServo.attach(10); // attaches the servo on pin 9 to the servo object
  irrecv.enableIRIn(); // Start the receiver

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  // Set the speed to start, from 0 (off) to 255 (max speed)
  motor1->setSpeed(speedy);
  motor1->run(FORWARD);
  // turn on motor
  motor1->run(RELEASE);

  angle = map(500, 0, 1023, 0, 179);
  myServo.write(angle);
}

void loop() {
  if (irrecv.decode(&results)) 
  {
    // get key being pressed
    x = results.value;
    Serial.println(x);

    // moving conditions
    if (x == 765)   // forward
    {
      motor1->run(FORWARD);
      motor1->setSpeed(speedy);
      delay(100);
    }
    else if (x == -32131)   // backward
    {
      motor1->run(BACKWARD);
      motor1->setSpeed(speedy);
      delay(100);
    }
    else if (x == 24735)   // right
    {
      location = 700;
      angle = map(location, 0, 1023, 0, 179);
      myServo.write(angle);
    }
    else if (x == -8161)   // left
    {
      location = 300;
      angle = map(location, 0, 1023, 0, 179);
      myServo.write(angle);
    }
    else if (x == 8925)   // stop
    {
      motor1->run(BACKWARD);
      motor1->setSpeed(0);
      location = 380;
      angle = map(location, 0, 1023, 0, 179);
      myServo.write(angle);
      delay(100);
    }
    
    
    // resume receiver
    irrecv.resume(); 
  }
}
