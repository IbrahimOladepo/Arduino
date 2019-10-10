int sPin = 2;
int in1 = 3;
int in2 = 4;
int ePin = 9;

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  pinMode(sPin, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ePin, OUTPUT);
  digitalWrite(ePin, HIGH);
} 

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(sPin) == HIGH)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);  
  }
  else
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);  
  }
}
