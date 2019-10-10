#include <IRremote.h>
// #include <stdlib.h>

int RECV_PIN = 11;
int codeType = -1;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop()
{
  if (irrecv.decode(&results))
    {
     Serial.println(results.value, HEX);
     //Serial.print("results value is: ");
     //Serial.println(results->value);
     //codeType = results->decode_type;

     /*
     if (results->decode_value == 551542815)
     {
       Serial.println("To the left!!"); 
     }*/
     irrecv.resume(); // Receive the next value
     //unsigned int button = strtol(results.value, NULL, 16);
     //Serial.println(button);
    }
  // 20DFE01F - left
}
