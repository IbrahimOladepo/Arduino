//Connections:  MOSI - pin 11, MISO - pin 12, CLK - pin 13, CS - pin 10

#include <SD.h>
#include <SPI.h>
 
int cs = 4; // Set Chip Select to pin ten

File myFile;  // a File Object

// defines pins numbers
const int trigPin = 8;
const int echoPin = 9;

// defines variables
long duration;
int distance;

void setup()
{
  //
  char myFileName[] = "MyFile.txt";  // The name of the file we will create
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    
  }
  Serial.println("Initializing SD card...");
  Serial.println();
  
  pinMode(cs, OUTPUT);
  
  // Documentation says you're supposed to do this
  // even if you don't use it:
  pinMode(SS, OUTPUT);
   
  // see if the card is present and can be initialized:
  if (!SD.begin(cs)) {
    Serial.println("SD did not initiliaze");   
    while (1) ;
  }
  Serial.println("SD initialized.");
 
 
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

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
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
  
  // Calculating the distance
  distance= duration * 0.034 / 2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  // make a string for assembling the data to log:
  String dataString = String(distance);

  // print to the serial port too:
  Serial.println(dataString);

  // The following line will 'save' the file to the SD card after every
  // line of data - this will use more power and slow down how much data
  // you can read but it's safer! 
  myFile.flush();

  // Take 1 measurement every 500 milliseconds
  delay(2000);
}
