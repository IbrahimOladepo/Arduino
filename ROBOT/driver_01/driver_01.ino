//Four Motors
int LF = 5;

void setup()  {
  Serial.begin(9600);  
} 

void loop()  {
  
  analogWrite(LF, 255);
  delay(5000);
  Serial.println(HIGH);
  analogWrite(LF, 0);
  delay(5000);
  Serial.println(LOW);
  
}
