#include <SoftwareSerial.h>
#include <Wire.h>

#define DEBUG 1
#define IP "184.106.153.149" // ThingSpeak IP Address: 184.106.153.149

SoftwareSerial esp8266Module(2, 3);

// 63BQMW557OWIFLLG
String GET = "GET /update?key=63BQMW557OWIFLLG";

int fsr=A0;
// int fsr1=A1;
// int fsr2=A2;
// int fsr3=A3;
const float VCC=5.0;
const float R_div= 100000; // 1k resistor

int blink_time = 200;

void setup() {
  Serial.begin(9600);
  esp8266Module.begin(9600); 
  
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  // power indicator
  animateLED(5, 7);
  digitalWrite(7, HIGH);

  setupEsp8266();
}

void loop() {
  // String dataString = String(distance_m);
  float fsr_val=analogRead(A0);
  if(fsr_val !=0)
  {
    float fsrV= fsr_val * VCC/1023;
    float fsrR= R_div * (VCC/fsrV-1.0);
    // Serial.println("Resistance"+String(fsrR) +"ohms");
    float force;
    float fsrG=1.0/fsrR;
    if(fsrR <= 600)
    {
      force=(fsrG - 0.00075)/0.00000032639;
    }
    else
    {
      force=fsrG/0.000000642857;
      if (isnan(force)) {
        if (DEBUG) Serial.println("Failed to read from sensor");
      }
      else {
        if (DEBUG)  Serial.println("force="+String(force)+" g");
        thingSpeakWrite(force);   // Write values to thingspeak     
        delay(20000);  
      }
    }
  }
}

//-------------------------------------------------------------------
// Following function setup the esp8266, put it in station made and 
// connect to wifi access point.
//------------------------------------------------------------------
void setupEsp8266()                                   
{
    // Serial.println("Reseting esp8266");
    animateLED(3, 8);
    esp8266Module.flush();
    esp8266Module.println("AT+RST");
    delay(10000);
    if (esp8266Module.find("OK"))
    {
      animateLED(2, 8);
      esp8266Module.flush();
      changingMode();
      delay(5000);
      esp8266Module.flush();
      connectToWiFi();
    }
    else
    {
      // Serial.println("OK not found");
      animateLED(12, 9);
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
      // Serial.println("Mode changed");
      return true;
    }
    else if(esp8266Module.find("NO CHANGE")){
      // Serial.println("Already in mode 1");
      return true;
    }
    else
    {
      // Serial.println("Error while changing mode");
      return false;
    }
}

//-------------------------------------------------------------------
// Following function connects esp8266 to wifi access point
//-------------------------------------------------------------------
bool connectToWiFi()
{
  // Serial.println("inside connectToWiFi");
  animateLED(5, 8);  
  String cmd = "AT+CWJAP=\"";
  cmd += "IBTECH";        // CHANGE WI-FI NAME
  cmd += "\",\"";
  cmd += "12345678";    // CHANGE WI-FI PASSWORD
  cmd += "\"";
  esp8266Module.println(cmd);
  delay(5000);
  
  if (esp8266Module.find("OK"))
  {
    // Serial.println("Connected to Access Point");  
    animateLED(2, 8); 
    return true;
  }
  else
  {
    // Serial.println("Could not connect to Access Point");
    animateLED(2, 9); 
    return false;
  }
}

//-------------------------------------------------------------------
// Following function sends sensor data to thingspeak.com
//-------------------------------------------------------------------
void thingSpeakWrite(float distance)
{  
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149";
  cmd += "\",80";
  esp8266Module.println(cmd);
  delay(5000);
  if(esp8266Module.find("Error")){
    // Serial.println("ERROR while SENDING");
    animateLED(2, 9);
    return;
  }
  cmd = GET + "&field1=" + String(distance) + "\r\n";
  esp8266Module.print("AT+CIPSEND=");
  esp8266Module.println(cmd.length());
  delay(15000);
  if(esp8266Module.find(">"))
  {
    esp8266Module.print(cmd);
    // Serial.println("Data sent");
    animateLED(3, 8);
  }
  else
  {
    esp8266Module.println("AT+CIPCLOSE");
    // Serial.println("Connection closed");  
    animateLED(4, 9);
  }
}

void animateLED(int blink_no, int pin_no)
{  
  while(blink_no > 0){
    digitalWrite(pin_no, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(blink_time);                       // wait for a second
    digitalWrite(pin_no, LOW);    // turn the LED off by making the voltage LOW
    delay(blink_time);

    blink_no = blink_no - 1;
  }
}
