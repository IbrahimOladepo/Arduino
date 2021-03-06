#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal.h> // includes the LiquidCrystal Library
#include <SD.h>
#include <SPI.h>

LiquidCrystal lcd(19, 18, 17, 16, 15, 14); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)

#define DEBUG 1
#define rxPin 6
#define txPin 7
#define IP "184.106.153.149" // ThingSpeak IP Address: 184.106.153.149

int cs = 10; // Set Chip Select to pin ten

File myFile;  // a File Object

// defines pins numbers
const int trigPin = 8;
const int echoPin = 9;

// defines variables
long duration;
int distance;
String val;

SoftwareSerial esp8266Module(rxPin, txPin);               // RX, TX

String network = "PC-Faster-8672";             // your access point SSID
String password = "12345678";                  // your wifi Access Point password                       // IP address of thingspeak.com
String GET = "GET /update?key=FAGT3WUKJJR4FOCI";    // replace with your channel key

void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  if(DEBUG){
    Serial.begin(9600);                             // Setting hardware serial baud rate to 9600
  }  
  esp8266Module.begin(9600);                        // Setting softserial baud rate to 9600
  delay(2000);

  setupEsp8266();  

  char myFileName[] = "MyFile.txt";  // The name of the file we will create

  lcd.begin(16,2);
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    
  }
  Serial.println("Initializing SD card...");
  lcder("Initializing","SD card ...");
  Serial.println();
  
  pinMode(cs, OUTPUT);
  
  // Documentation says you're supposed to do this
  // even if you don't use it:
  pinMode(SS, OUTPUT);
   
  // see if the card is present and can be initialized:
  if (!SD.begin(cs)) {
    Serial.println("SD did not initiliaze");
    lcder("Error SD did", "initiliaze!!");   
    while (1) ;
  }
  Serial.println("SD initialized.");
  lcder("SD inited","     ");
 
 
 // Lets check to make sure that the SD card doesn't already have our file
  if (! SD.exists(myFileName)){
     // This next statement will open a file for writing if it exists
     // If it does not exist, it will create that file. That's what we're doing here.
     myFile = SD.open(myFileName, FILE_WRITE); 
     // This next statement checks to see if the file
     myFile.println("My 1st Line of Data");  // Send Your First Line to that file
     myFile.flush();  // Save it.
  }
  else{
    // We got here because the file already exists.
    // Therefore we're simple opening the file and writing to it. We will add another line at the end.   
    myFile = SD.open(myFileName, FILE_WRITE); 
    myFile.println("Another Line of Data");  // Send Your First Line to that file
    myFile.flush();
    
  }
  
  Serial.println("Done Writing");
  lcder("Done writing", "     ");
}

void loop() 
{                                
    
  int level = dist();

  // make a string for assembling the data to log:
  String dataString = String(level);
  
  myFile.println(dataString);

  // print to the serial port too:
  Serial.println(dataString);

  // SD card is filled with data.
  myFile.flush();

  // display value on LCD
  val = String(level);
  lcder("distance", val);
  
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
  delay(25000);
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
  lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print(nameofvalue); // Prints string "Distance" on the LCD
  lcd.setCursor(0,1);
  lcd.print(valuetodisplay); // Prints the distance value from the sensor
  lcd.print(" cm");
}
