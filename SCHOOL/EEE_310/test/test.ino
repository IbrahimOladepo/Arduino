#include<LiquidCrystal.h>
#include<lm35.h>

LiquidCrystal lcd(12,11,10,9,8,7);

#define pwm 6
#define in 15
#define out 16

int A = 0;
int B;
int count = 0;
int sensorpin = A0;
int min_temp = 5;
int mid_temp = 10;
int max_temp = 28;
float inner;
float outer;

lm35 temps(A0);

void IN()
{
  count = count + 1;
  lcd.clear();
  lcd.print("PERSON IN ROOM");
  lcd.setCursor(0,1);
  lcd.print(count);
  delay(4000);
}

void OUT()
{
  count = count - 1;
  lcd.clear();
  lcd.print("PERSON IN ROOM");
  lcd.setCursor(0,1);
  lcd.print(count);
  delay(4000);
}

void setup() 
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.print("VISITOR COUNTER");
  delay(1000);
  lcd.clear();
  lcd.print("PERSON IN ROOM:");
  
  pinMode(pwm,OUTPUT);
  pinMode(in, INPUT);
  pinMode(out, INPUT);
}

void loop()
{
  A = analogRead(sensorpin); // get the temprature
  B = (500* A / 1024);
  if (B < 0)
  {
    B = B * -1;
  }
  
  inner = (analogRead(in)) * (5.0 / 1023.0);
  Serial.print("INNER IS : ");
  Serial.println(inner);
  
  if(inner > 3)
    {
      IN();
    }

  outer = (analogRead(out)) * (5.0 / 1023.0);
  if(outer > 100)
  {
    if (count > 0)
    {
      OUT();
      }
      else
      {
        lcd.print("NOBODY IN ROOM");
      }
    }
  if(count <= 0)
  {
    lcd.clear();
    lcd.print("NOBODY IN ROOM");
    lcd.setCursor(0,1);
    lcd.print("FAN IS OFF");
    delay(500);
    analogWrite(pwm, 0);
  }

  else
  {
    if(B <= mid_temp )   // if temperature is lower than minimum temp
     {
       analogWrite(pwm, 0);
     }
    else if(B > mid_temp && B <= max_temp)
     {
       analogWrite(pwm, 128);
     }
     else if(B > max_temp)
     {
       analogWrite(pwm, 255); 
     }
     
     lcd.clear();
     lcd.print("TEMPARATURE = ");
     lcd.setCursor(0,1);
     lcd.print(B);
  }

  Serial.print("COUNT IS : ");
  Serial.println(count);
  Serial.print("TEMPARATURE IS : ");
  Serial.println(B);

  inner = 0;
  outer = 0;
 }
