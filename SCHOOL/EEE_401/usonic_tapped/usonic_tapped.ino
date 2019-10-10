/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* Crated by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/

// defines pins numbers
const int echoPin = 7;

// defines variables
int mapped;
int distance;

void setup() {
  pinMode(14, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  distance = analogRead(14);

  // serial display
  Serial.println("mapped distance is: ");
  Serial.println(distance);

  delay(2000);
}
