#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal.h> // includes the LiquidCrystal Library

LiquidCrystal lcd(19, 18, 17, 16, 15, 14);

#define DEBUG 1
#define rxPin 6
#define txPin 7
#define IP "184.106.153.149" // ThingSpeak IP Address: 184.106.153.149

// defines pins numbers
const int trigPin = 8;
const int echoPin = 9;

// on/off sensor
long duration;
int distance_m;

SoftwareSerial esp8266Module(rxPin, txPin);               // RX, TX

String network = "PC-Faster-8672";             // your access point SSID
String password = "12345678";                  // your wifi Access Point password                       // IP address of thingspeak.com
String GET = "GET /update?key=FAGT3WUKJJR4FOCI";    // replace with your channel key

void setup()
{
  lcd.begin(16,2);
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  if(DEBUG){
    Serial.begin(9600);                             // Setting hardware serial baud rate to 9600
  }  
  esp8266Module.begin(9600);                        // Setting softserial baud rate to 9600
  delay(2000);

  setupEsp8266();  
}

void loop() 
{                                
    
  int level = dist();

  // display value on LCD
  // val = String(level);
  lcder("distance", String(level));
  
  updateLevel(String(level));
  delay(20000);
}

//-------------------------------------------------------------------
// Following function setup the esp8266, put it in station made and 
// connect to wifi access point.
//------------------------------------------------------------------
void setupEsp8266()                                   
{
    if(DEBUG){
      Serial.println("Reseting esp8266");
    }
    esp8266Module.flush();
    esp8266Module.println("AT+RST");
    delay(7000);
    if (esp8266Module.find("OK"))
    {
      if(DEBUG){
        Serial.println("Found OK");
        Serial.println("Changing espmode");
      }  
      esp8266Module.flush();
      changingMode();
      delay(5000);
      esp8266Module.flush();
      connectToWiFi();
    }
    else
    {
      if(DEBUG){
        Serial.println("OK not found");
      }
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
      if(DEBUG){
        Serial.println("Mode changed");
      }  
      return true;
    }
    else if(esp8266Module.find("NO CHANGE")){
      if(DEBUG){
        Serial.println("Already in mode 1");
      }  
      return true;
    }
    else
    {
      if(DEBUG){
        Serial.println("Error while changing mode");
      }  
      return false;
    }
}

//-------------------------------------------------------------------
// Following function connects esp8266 to wifi access point
//-------------------------------------------------------------------
bool connectToWiFi()
{
  if(DEBUG){
    Serial.println("inside connectToWiFi");
  }  
  String cmd = "AT+CWJAP=\"";
  cmd += network;
  cmd += "\",\"";
  cmd += password;
  cmd += "\"";
  esp8266Module.println(cmd);
  delay(15000);
  
  if (esp8266Module.find("OK"))
  {
    if(DEBUG){
      Serial.println("Connected to Access Point");
    }  
    return true;
  }
  else
  {
    if(DEBUG){
      Serial.println("Could not connect to Access Point");
    }  
    return false;
  }
}

//-------------------------------------------------------------------
// Following function sends sensor data to thingspeak.com
//-------------------------------------------------------------------
void updateLevel(String distance)
{  
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80";
  esp8266Module.println(cmd);
  delay(5000);
  if(esp8266Module.find("Error")){
    if(DEBUG){
      Serial.println("ERROR while SENDING");
    }  
    return;
  }
  cmd = GET + "&field1=" + distance + "\r\n";
  esp8266Module.print("AT+CIPSEND=");
  esp8266Module.println(cmd.length());
  delay(15000);
  if(esp8266Module.find(">"))
  {
    esp8266Module.print(cmd);
    if(DEBUG){
      Serial.println("Data sent");
    }
  }else
  {
    esp8266Module.println("AT+CIPCLOSE");
    if(DEBUG){
      Serial.println("Connection closed");
    }  
  }
}

int dist()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  int duration = pulseIn(echoPin, HIGH);
  Serial.print("Duration: ");
  Serial.println(duration);
  
  // Calculating the distance
  int distance_m = duration * 0.034 / 2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance_m);

  return distance_m;
}

void lcder(String nameofvalue, String valuetodisplay)
{
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print(nameofvalue); // Prints string "Distance" on the LCD
  lcd.setCursor(0,1);
  lcd.print(valuetodisplay); // Prints the distance value from the sensor
  lcd.print(" cm");
}
