// documentations
/*
 * MQ5 CONNECTION
 * VCC  -----> VCC
 * GND  -----> GND
 * AD   -----> A0
 * 
 * SD CARD ATTACHED TO SPI BUS AS FOLLOWS:
 * MOSI -----> pin 11
 * MISO -----> pin 12
 * CLK  -----> pin 13
 * CS   -----> pin 10
 * 
 * RTC ATTACHED TO ARDUINO AS FOLLOWS:
 * SDA  -----> Arduino Analog 4 or the dedicated SDA pin
 * SCL  -----> Arduino Analog 5 or the dedicated SCL pin
 * 
 * BUZZER ATTACHED TO ARDUINO AS FOLLOWS:
 * +    -----> pin 3
 */



// includes
#include <SPI.h>
#include <SD.h>
#include <DS3231.h>


// initializations
float smoke_level = 0;
float smoke_volt = 0;
const int chipSelect = 10;
String dataString = "";

DS3231  rtc(SDA, SCL);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  
  pinMode(A0, INPUT);
  pinMode(3, OUTPUT);


  // SD CARD INITIALIZATION
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");


  // Initialize the rtc object
  rtc.begin();
}


void beepbeep(int rate)
{
  float timedelay =   140 - (rate * 100);
  
  // buzzer sound alarm
  digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(timedelay);              // wait for a second
  digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW
  delay(timedelay);
  digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(timedelay);              // wait for a second
  digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW
  delay(timedelay);
  digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(timedelay);              // wait for a second
  digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW
}


void loop() {
  // put your main code here, to run repeatedly:
  smoke_level = analogRead(A0);
  smoke_volt = smoke_level / 1024 * 5.0;

  Serial.print("Smoke Level voltage is: ");
  Serial.println(smoke_volt);

  if (smoke_volt > 0.88){
    // buzzer sound alarm
    beepbeep(smoke_volt);
  
    // data to save in SD Card
    dataString = "";
  
    // concatenate date and time
    dataString += rtc.getDateStr();
    dataString += ",";
    dataString += rtc.getTimeStr();
    dataString += ",";
  
    // open the file
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
    // if the file is available, write to it:
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      // print to the serial port too:
      Serial.println(dataString);
    }
    // if the file isn't open, pop up an error:
    else {
      Serial.println("error opening datalog.txt");
    }
  
    delay(2000);
  }
}
