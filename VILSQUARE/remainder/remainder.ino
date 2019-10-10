#include <DS3231.h>
#include <SPI.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SD.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);
File  myFile;
//#include <DS1302.h>
String mystring = "";
String drug1 = "";
String drug2 = "";
int settime1  = 0;
int settime2  = 0;
int Hour;
int Min;
int pset = 8; // pushbutton for setting alarm
int phour = 9; // pushbutton for hour
int pmin = 10; // pushbutton for minutes
int pexit = 3; // pushbutton for exit of set alarm
int buzzer = 6;
int led = 5;
int h;
int m;
int buttonforset = 0; // pushbutton state for setting alarm
int buttonforhour = 0; // pushbutton state for hour
int buttonformin = 0;// pushbutton state for minutes
int buttonforexit = 0; // pushbutton state for exit of set alarm
int activate=0;
 
Time t;

DS3231  rtc(SDA, SCL);

void parsecsv(String data);

void setup()
{
 pinMode(pset, OUTPUT);
 pinMode(phour, OUTPUT);
 pinMode(pmin, OUTPUT);
 pinMode(pexit, OUTPUT);
 pinMode(led, OUTPUT);
 pinMode(buzzer, OUTPUT);
 Serial.begin(9600);
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
   myFile = SD.open("TEST.txt");
  delay(10);
  if (myFile) {
    Serial.println("TEST.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      mystring += (char)myFile.read();
    }
        Serial.println(drug1);
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  parsecsv(mystring);
 rtc.begin();
 lcd.init();                      // initialize the lcd 
 lcd.backlight();
 Serial.begin(9600);


 // Setup LCD to 16x2 character

// The following lines can be commented out to use the values already stored in the DS1302
 // rtc.setDOW(SATURDAY); // Set Day-of-Week to FRIDAY
 // rtc.setTime(2, 8, 0); // Set the time to 12:00:00 (24hr format)
 //rtc.setDate(28, 7, 2018); // Set the date to August 6th, 2010
}

void parsecsv(String data){
  int con = 0;
  int con1  = 0;
  String  temp1="";
  String temp2="";
  String temp3="";
  String temp4="";
  for (int  i=0;  i<data.length();i++){
    if  (con  ==  0){
      if(data[i]==',')
            con = 1;
      else
        temp1+=data[i];
    }
    else  if (con == 1){
       if(data[i]==',')
            con = 2;
      else              
          temp2 += data[i];
    }
    else if(con == 2){
         if(data[i]==',')
            con = 3;
      else
        temp3+=data[i];
    }
    else{
        if(data[i]==',')
            continue;
        else
          temp4+=data[i];
    }
  }
  Serial.println(temp1);
  drug1 = temp1;
  Serial.println(temp2);
  settime1 =temp2.toInt();
  Serial.println(temp3);
  drug2 = temp3;
  Serial.println(temp4);
  settime2 = temp4.toInt();
}

void loop()
{
 // digitalWrite(pset,LOW);
 if (activate == 0) {

// Display time on the right conrner upper line
 lcd.setCursor(0, 0);
 lcd.print("Time: ");
 lcd.setCursor(6, 0);
 lcd.print(rtc.getTimeStr());
 
 // Display abbreviated Day-of-Week in the lower left corner
 lcd.setCursor(0, 1);
 lcd.print(rtc.getDOWStr(FORMAT_SHORT));
 
 // Display date in the lower right corner
 lcd.setCursor(0, 1);
 lcd.print("Date: ");
 lcd.setCursor(6, 1);
 lcd.print(rtc.getDateStr());
 t = rtc.getTime();
 Hour = t.hour;
 Min = t.min;
 buttonforset = digitalRead(pset);
 } 
 buttonforset = digitalRead(pset);
 Serial.println(buttonforset);
 
 digitalWrite(pset,LOW);
 // setting button pressed
 
  if(buttonforset == HIGH) 
      {
        Serial.println("I'm here");
        activate =1;
        lcd.clear();  
      }

 
 while(activate== 1){
 lcd.setCursor(0,0);
 lcd.print("Set Alarm");
 lcd.setCursor(0,1);
 lcd.print("Hour= ");
 lcd.setCursor(9,1);
 lcd.print("Min= ");
 buttonforhour = digitalRead(phour); 
 
 
 // set hour for alarm
 if (buttonforhour == HIGH){
 h++;
 lcd.setCursor(5,1);
 lcd.print(h);
 if (h>23){
 h=0;
 lcd.clear(); }
 delay(100); 
 }
 buttonformin = digitalRead(pmin); 
 
 
 // set minutes for alarm
 if (buttonformin == HIGH){
 m++;
 lcd.setCursor(13,1);
 lcd.print(m);
 if (m>59){
 m=0; 
 lcd.clear();}
 delay(100); 
 }

lcd.setCursor(5,1);
 lcd.print(h);
 lcd.setCursor(13,1);
 lcd.print(m);
 buttonforexit = digitalRead(pexit); // exit from set alarm mode
 if (buttonforexit == HIGH){
 activate = 0;
 lcd.clear();
 }
 }
 
 if (Hour== h && Min== m) {
 tone(6,400,300);
 digitalWrite(led, HIGH);lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("NA TIME FOR PARACETAMOL O");
   lcd.setCursor(0,1);
   lcd.print("2 DOSES");}
   else{
    digitalWrite(led, LOW);
   }
 delay (500);

   
   /*for (int i = 1; i < 6; i++){
   digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
   digitalWrite(6, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);              // wait for a second
    digitalWrite(5, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(6, LOW);    // turn the LED off by making the voltage LOW
    delay(100);
    digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(6, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);              // wait for a second
    digitalWrite(5, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(6, LOW);    // turn the LED off by making the voltage LOW
    delay(100);
    digitalWrite(5, HIGH);    // turn the LED off by making the voltage LOW
    digitalWrite(6, HIGH);    // turn the LED off by making the voltage LOW
    delay(600);              // wait for a second
    digitalWrite(5, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(6, LOW);    // turn the LED off by making the voltage LOW*/
  
   lcd.clear();
 
}

