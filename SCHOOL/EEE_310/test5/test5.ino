float a = 0;
float b = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  a = digitalRead(A0);
  b = digitalRead(A1);
  
  Serial.println(a);
  //Serial.print(',');
  //Serial.println(b);
  delay(1000); 
}
