// initializations
float smoke_level = 0;
float smoke_volt = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);

  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  smoke_level = analogRead(A1);
  smoke_volt = smoke_level / 1024 * 5.0;

  Serial.print("Smoke Level voltage is: ");
  Serial.println(smoke_volt);

  delay(2000);
}
