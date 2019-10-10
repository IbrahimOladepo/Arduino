#include<LiquidCrystal.h>

LiquidCrystal lcd(12,11,10,9,8,7);

#define in 15
#define out 16
#define relay 6
#define tempPin 16

int dat, val;

int count = 0;
int temp;
int direct = 0;
float  cel = ((temp / 1024.0)*5000) / 10;
float speed;


void IN()
{
  count++;
  lcd.clear();
  lcd.print("PEOPLE IN ROOM");
  lcd.setCursor(0,1);
  lcd.print(count);
  digitalWrite(0, HIGH);
  delay(2000);
}

void OUT()
{
  count--;
  lcd.clear();
  lcd.print("PEOPLE IN ROOM");
  lcd.setCursor(0,1);
  lcd.print(count);
  digitalWrite(0, LOW);
  delay(2000);
}

void setup()
{
  Serial.begin(9600);

  lcd.begin(16,2);
  lcd.print("Automatic Fan");
  delay(1000);
  lcd.print("With Visitor Counter");
  delay(1000);
  pinMode(in, INPUT);
  pinMode(out, INPUT);
  pinMode(relay, OUTPUT);
  lcd.clear();
  lcd.print("Person In Room:");
  lcd.setCursor(0,1);
}

void loop()
{
  // coming in part
  if(digitalRead(in))
  {
    IN();
    //direct = 1;
  }

  // going out part
  if(digitalRead(out))
  {
    OUT();
    //direct = 2;
  }

  if(count <= 0)
  {
    //digitalWrite(relay, LOW);
    lcd.clear();
    lcd.print("Nobody In Room");
    lcd.setCursor(0,1);
    lcd.print("Light is Off");
    delay(1000);
  }
  else
    lcd.clear();
    val = analogRead(A0);
    dat = (val*500)>>10;
    lcd.setCursor(0,0);
    lcd.print("TEMPRATURE = ");
    lcd.setCursor(0,1);
    lcd.print(dat);
    delay(1000);
}

