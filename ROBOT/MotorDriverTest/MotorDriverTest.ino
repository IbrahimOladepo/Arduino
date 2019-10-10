#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1 and M2
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  // Set the speed to start, from 0 (off) to 255 (max speed)
  motor1->setSpeed(50);
  motor1->run(FORWARD);
  // turn on motor
  motor1->run(RELEASE);

  motor2->setSpeed(50);
  motor2->run(BACKWARD);
  // turn on motor
  motor2->run(RELEASE);
}

void loop() {
  uint8_t i;
  
  Serial.print("tick");

  motor1->run(FORWARD);
  motor2->run(BACKWARD);
  /*for (i = 100; i <= 255; i++) {
    motor1->setSpeed(i); 
    motor2->setSpeed(i);
    Serial.println(i); 
    delay(200);
  }
  for (i = 255; i != 100; i--) {
    motor1->setSpeed(i); 
    motor2->setSpeed(i); 
    Serial.println(i);
    delay(200);
  }*/
  motor1->setSpeed(70); 
  motor2->setSpeed(70);
  delay(5000);
}
