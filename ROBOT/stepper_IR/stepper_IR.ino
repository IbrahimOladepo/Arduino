#include <IRremote.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

int RECV_PIN = 7;
int x;

IRrecv irrecv(RECV_PIN);
decode_results results;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(48, 2);

void setup()
{
  Serial.begin(9600);
  Serial.println("Stepper test!");
  irrecv.enableIRIn(); // Start the receiver

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  myMotor->setSpeed(20);  // 10 rpm   
}

void loop() {
  if (irrecv.decode(&results)) {
    // get key being pressed
    x = results.value;
    Serial.println(x);

    // moving conditions
    if (x == 14535)   // forward
    {
      myMotor->step(20, FORWARD, SINGLE); 
      delay(200);
    }
    else if (x == 6375)   // backward
    {
      myMotor->step(20, BACKWARD, SINGLE);
      delay(200); 
    }
  }
  delay(100);
}
