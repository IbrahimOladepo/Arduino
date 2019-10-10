float a = 0;
float b = 0;
int count = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  a = analogRead(A1);
  //b = analogRead(A2);
  
  if (a > 0)
  {
    Serial.print("A IS : ");
    Serial.println(a);
    count = count + 1;
    //delay(2000);  
  }

  
  /*if (b > 0 && count > 0)
  {
    Serial.print("B IS : ");
    Serial.println(b);
    count = count - 1;
    //delay(1000);  
  }*/
   Serial.print("A IS : ");
    Serial.println(a);
  //Serial.print("B IS : ");
    //Serial.println(b);
    delay(1000); 
}
