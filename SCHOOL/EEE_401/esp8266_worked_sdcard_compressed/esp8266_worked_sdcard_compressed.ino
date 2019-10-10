#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal.h> // includes the LiquidCrystal Library
#include <SD.h>
#include <SPI.h>

LiquidCrystal lcd(19, 18, 17, 16, 15, 14);

#define DEBUG 1
#define IP "184.106.153.149" // ThingSpeak IP Address: 184.106.153.149

int cs = 10; // Set Chip Select to pin ten
File myFile;  // a File Object

// defines pins numbers
const int trigPin = 8;
const int echoPin = 9;

// on/off sensor
long duration;
int distance_m;

SoftwareSerial esp8266Module(6, 7);               // RX, TX

String GET = "GET /update?key=FAGT3WUKJJR4FOCI";    // replace with your channel key

void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(cs, OUTPUT);
  pinMode(SS, OUTPUT);
  
  lcd.begin(16,2);
  Serial.begin(9600);                             // Setting hardware serial baud rate to 9600
  esp8266Module.begin(9600);                        // Setting softserial baud rate to 9600

  Serial.println("Initializing SD card...");
  Serial.println();
  
  // see if the card is present and can be initialized:
  if (!SD.begin(cs)) {
    Serial.println("SD did not initiliaze");   
    while (1) ;
  }
  Serial.println("SD initialized.");
 
 // Lets check to make sure that the SD card doesn't already have our file
  if (! SD.exists("MyFile.txt")){
     // This next statement will open a file for writing if it exists
     // If it does not exist, it will create that file. That's what we're doing here.
     myFile = SD.open("MyFile.txt", FILE_WRITE); 
     // This next statement checks to see if the file
     myFile.println("My 1st Line of Data");  // Send Your First Line to that file
     myFile.flush();  // Save it.
  }
  else{
    // We got here because the file already exists.
    // Therefore we're simple opening the file and writing to it. We will add another line at the end.   
    myFile = SD.open("MyFile.txt", FILE_WRITE); 
    myFile.println("Another Line of Data");  // Send Your First Line to that file
    myFile.flush();
  }
  Serial.println("Done Writing");

  setupEsp8266();
}

void loop() 
{                                
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  Serial.print("Duration: ");
  Serial.println(duration);
  
  // Calculating the distance
  distance_m = duration * 0.034 / 2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance_m);

  // display value on LCD
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print("Distance:"); // Prints string "Distance" on the LCD
  lcd.setCursor(0,1);
  lcd.print(distance_m); // Prints the distance value from the sensor
  lcd.print(" cm");
  
  updateLevel(String(distance_m));
  delay(15000);

  // make a string for assembling the data to log:
  String dataString = String(distance_m);
  
  myFile.println(dataString);

  // print to the serial port too:
  Serial.println(dataString);

  // SD card is filled with data.
  myFile.flush();
  
  delay(10000);
}

//-------------------------------------------------------------------
// Following function setup the esp8266, put it in station made and 
// connect to wifi access point.
//------------------------------------------------------------------
void setupEsp8266()                                   
{
    Serial.println("Reseting esp8266");
    esp8266Module.flush();
    esp8266Module.println("AT+RST");
    delay(7000);
    if (esp8266Module.find("OK"))
    {
      Serial.println("Found OK");
      Serial.println("Changing espmode");
      esp8266Module.flush();
      changingMode();
      delay(5000);
      esp8266Module.flush();
      connectToWiFi();
    }
    else
    {
      Serial.println("OK not found");
    }
}

//-------------------------------------------------------------------
// Following function sets esp8266 to station mode
//-------------------------------------------------------------------
bool changingMode()
{
    esp8266Module.println(F("AT+CWMODE=1"));
    if (esp8266Module.find("OK"))
    {
      Serial.println("Mode changed");
      return true;
    }
    else if(esp8266Module.find("NO CHANGE")){
      Serial.println("Already in mode 1");
      return true;
    }
    else
    {
      Serial.println("Error while changing mode");
      return false;
    }
}

//-------------------------------------------------------------------
// Following function connects esp8266 to wifi access point
//-------------------------------------------------------------------
bool connectToWiFi()
{
  Serial.println("inside connectToWiFi");
  String cmd = "AT+CWJAP=\"";
  cmd += "PC-Faster-8672";
  cmd += "\",\"";
  cmd += "12345678";
  cmd += "\"";
  esp8266Module.println(cmd);
  delay(10000);
  
  if (esp8266Module.find("OK"))
  {
    Serial.println("Connected to Access Point");  
    return true;
  }
  else
  {
    Serial.println("Could not connect to Access Point");
    return false;
  }
}

//-------------------------------------------------------------------
// Following function sends sensor data to thingspeak.com
//-------------------------------------------------------------------
void updateLevel(String distance)
{  
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149";
  cmd += "\",80";
  esp8266Module.println(cmd);
  delay(5000);
  if(esp8266Module.find("Error")){
    Serial.println("ERROR while SENDING");
    return;
  }
  cmd = GET + "&field1=" + distance + "\r\n";
  esp8266Module.print("AT+CIPSEND=");
  esp8266Module.println(cmd.length());
  delay(15000);
  if(esp8266Module.find(">"))
  {
    esp8266Module.print(cmd);
    Serial.println("Data sent");
  }
  else
  {
    esp8266Module.println("AT+CIPCLOSE");
    Serial.println("Connection closed");  
  }
}
