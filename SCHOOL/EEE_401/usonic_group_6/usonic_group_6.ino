/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* Crated by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/

// defines pins numbers
const int trigPin1 = 4;
const int echoPin1 = 5;
const int trigPin2 = 6;
const int echoPin2 = 7;
int motorPin = 9;
int buzzerPin = 10;

// defines variables
long duration1;
int distance1;
long duration2;
int distance2;

void setup() {
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  
  // Calculating the distance
  distance1 = duration1 * 0.034 / 2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance1: ");
  Serial.println(distance1);

  delay(100);

  // Clears the trigPin
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance2: ");
  Serial.println(distance2);

  delay(100);

  if (distance1 < 30 && distance2 < 30)
  {
    analogWrite(motorPin, 255);
    delay(5000);
    analogWrite(motorPin, 0);
  }
  else if(distance1 < 30 && distance2 > 30)
  {
    analogWrite(motorPin, 255);
    delay(5000);
    analogWrite(motorPin, 0);
  }
  else if(distance1 > 30 && distance2 < 30)
  {
    analogWrite(buzzerPin, 255);
    delay(5000);
    analogWrite(buzzerPin, 0);
  }
  else
  {
    analogWrite(motorPin, 0);
    analogWrite(buzzerPin, 0);
  }

  Serial.print("Motorpin is: ");
  Serial.println(motorPin);
  Serial.print("Buzzerpin is: ");
  Serial.println(buzzerPin);
}
