#include <IRremote.h>

int RECV_PIN = 6;
int x;
int in1 = 13;
int in2 = 12;
int in3 = 11;
int in4 = 10;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() 
{
  if (irrecv.decode(&results)) 
  {
    // get key being pressed
    x = results.value;

    // moving conditions
    if (x == 765)   // forward
    {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      //delay(1000);
    }
    else if (x == -32131)   // backward
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      //delay(1000);
    }

    // resume receiver
    irrecv.resume(); 
  }
}
