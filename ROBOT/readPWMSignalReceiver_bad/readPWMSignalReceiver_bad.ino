byte CH1_PIN = 2;
byte CH3_PIN = 3;
int ch1_value;
int ch3_value;
 
void setup() {
  pinMode(CH1_PIN, INPUT);
  pinMode(CH3_PIN, INPUT);
  
  Serial.begin(115200);
}
 
void loop() {
  // get values
  ch1_value = pulseIn(CH1_PIN, HIGH);   // channel 1: servo
  Serial.print("Channel 1 value is: ");
  Serial.println(ch1_value);
  delay(20);

  ch3_value = pulseIn(CH3_PIN, HIGH);   // channel 3: motor
  Serial.print("Channel 3 value is: ");
  Serial.println(ch3_value);
  delay(20);
}

