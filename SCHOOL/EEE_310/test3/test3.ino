/*
 * CS50 FINAL PROJECT
 * 
 * OLADEPO IBRAHIM
 * ibrahim.oladepo@yahoo.com
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

// define variables
#define theta 14
#define in 15
#define out 16

int A = 0;
int B = 0;
int temp = 0;
int count = 0;

void setup()
{
  // Serial.begin(9600);
  lcd.begin(16, 2);

  // define pin modes
  pinMode(in, INPUT);
  pinMode(out, INPUT);
  pinMode(theta, INPUT);
  pinMode(3, OUTPUT);

  // initial LCD display
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print("CS50 FINAL");
  lcd.setCursor(0,1);
  lcd.print("PROJECT");
  delay(100);
}

void loop()
{
  A = digitalRead(in);
  B = digitalRead(out);
  
  if (!A)
  {
    IN();  
  }
  
  if (!B)
  {
    OUT(); 
  }

  if (count > 0)
  {
    temp = (500 * (analogRead(theta)) / 1024);
    if (temp < 0)
    {
      temp = temp * -1;
    }
    tempmessage();
    if (temp > 24)  // hot temparature
    {
      digitalWrite(3, HIGH);
    }  
    delay(100);
  }
  else
  {
    digitalWrite(3, LOW);  
  }
}

// input function
void IN()
{
  count = count + 1;
  message();
  delay(1000);
}

// output function
void OUT()
{
  if (count > 0)
  {
    count = count - 1;
  }
  message();
  delay(1000);
}

// display room content
void message()
{
  lcd.clear();
  lcd.print("ROOM CONTAINS:");
  lcd.setCursor(0,1);
  if (count <= 0)
  {
    lcd.print("NO ONE");
  }
  else if (count == 1)
  {
    lcd.print(count);
    lcd.print(" PERSON");
  }
  else if (count > 1)
  {
    lcd.print(count);
    lcd.print(" PEOPLE"); 
  }  
}

// display tempatature message
void tempmessage()
{
  lcd.clear();
  lcd.print("ROOM TEMP:");
  lcd.setCursor(0,1);
  lcd.print(temp);
}
