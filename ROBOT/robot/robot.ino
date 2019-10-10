#include <IRremote.h>
#include <Servo.h>

int RECV_PIN = 11;
int servo_pin = 7;
int pwmPin = 5;

int potValue = 380;
int x;

IRrecv irrecv(RECV_PIN);
Servo myServo;

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  myServo.attach(servo_pin);
}

void loop() 
{
  if (irrecv.decode(&results)) 
  {
    myServo.write(map(potValue, 0, 1023, 0, 180));

    // get key being pressed
    x = results.value;

    // moving conditions
    if (x == 765)   // forward
    {
      analogWrite(pwmPin, 32);
      Serial.println("Forward");
    }
    else if (x == -32131)   // backward
    {
      analogWrite(pwmPin, 0);
      Serial.println("Backward");
    }
    
    // steering conditions
    if (x == -8161)   // left
    {
      potValue = (potValue + 100) % 1023;
      myServo.write(map(potValue, 0, 1023, 0, 180));
      Serial.println("Left"); 
    }
    else if (x == 24735)   // right
    {
      potValue = (potValue - 100) % 1023;
      myServo.write(map(potValue, 0, 1023, 0, 180)); 
      Serial.println("Right");
    }

    // return x to zero
    x = 0;

    // resume receiver
    irrecv.resume(); 
  }
}
