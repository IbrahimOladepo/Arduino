int pwmPin = 5;

void setup() 
{
  Serial.begin(9600);
    pinMode( pwmPin, OUTPUT);
}

void loop () 
{
    int potValue = analogRead(A0);
    int newpotValue = map(potValue, 0, 1023, 0 , 255);
    analogWrite(pwmPin, newpotValue);
    Serial.println(newpotValue);
}

