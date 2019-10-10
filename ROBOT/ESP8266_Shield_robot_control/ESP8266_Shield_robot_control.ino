/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 *
 * This example shows how to use ESP8266 Shield (with AT commands)
 * to connect your project to Blynk.
 *
 * Note: Ensure a stable serial connection to ESP8266!
 *       Firmware version 1.0.0 (AT v0.22) is needed.
 *       You can change ESP baud rate. Connect to AT console and call:
 *           AT+UART_DEF=9600,8,1,0,0
 *       In general, Soft Serial may be unstable.
 *       It is highly recommended to switch to Hard Serial.
 *
 * Change WiFi ssid, pass, and Blynk auth token to run :)
 * Feel free to apply it to any other example. It's simple!
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// create a servo object
Servo myServo;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1 and M2
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

// Necessary variables
int speedy = 125;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
// char auth[] = "ddf12b21760c481dab38441b69649154"; robota
char auth[] = "e4d83457c6ac4f5d9b4b07992fd8b22c";

// Your WiFi credentials.
/*
// Set password to "" for open networks.
char ssid[] = "PC-Faster-7942";
char pass[] = "uvdvxupm";
*/
// network 2
char ssid[] = "IBTECH";
char pass[] = "";

// Hardware Serial on Mega, Leonardo, Micro...
// #define EspSerial Serial1

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(6, 7); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

void setup()
{
  // Set console baud rate
  Serial.begin(115200);
  delay(10);
  
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);

  // attaches the servo on pin 10 to the servo object
  myServo.attach(10);

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

  myServo.write(90);
}

// virtual stop button
BLYNK_WRITE(V0) {
  int stopper = param.asInt();
  Serial.print("STOP = ");
  Serial.println(stopper);

  // stop condition
  if (stopper == 1)
  {
    motor1->run(BACKWARD);
    motor2->run(FORWARD);
    motor1->setSpeed(0); 
    motor2->setSpeed(0);  
  }
}

// virtual speed button
BLYNK_WRITE(V1) {
  speedy = param.asInt();
  Serial.print("SPEEDY = ");
  Serial.println(speedy);

  motor1->setSpeed(speedy); 
  motor2->setSpeed(speedy);

  // set global speed
  // speedy = speedo;
}

// virtual angle button
BLYNK_WRITE(V2) {
  int angle = param.asInt();
  Serial.print("ANGLE = ");
  Serial.println(angle);

  // steering
  myServo.write(angle);  
}

// virtual steering button
BLYNK_WRITE(V3) {
  int dir = param.asInt();
  Serial.print("DIRECTION = ");
  Serial.println(dir);
  
  // set motion
  if (dir == 1)   // forward
  {
    motor1->run(FORWARD);
    motor2->run(BACKWARD);
    motor1->setSpeed(speedy); 
    motor2->setSpeed(speedy);
  }
  else   // backward
  {
    motor1->run(BACKWARD);
    motor2->run(FORWARD);
    motor1->setSpeed(speedy); 
    motor2->setSpeed(speedy);
  }
}

void loop()
{
  Blynk.run();
}

