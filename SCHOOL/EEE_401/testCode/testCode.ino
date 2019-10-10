char input=0;       //we receive input from BT module
int led1=4;   
int led2=8;   
void setup() {
  Serial.begin(96500);  //initiates serial communication
  pinMode(led1,OUTPUT); //sets pin as output
  pinMode(led2,OUTPUT); //sets pin as output
  Serial.println(">>START<<");  //displays "start"
}

void loop() {
  if(Serial.available()>0){   //checks input from BT
    input=Serial.read();      //reads input from BT
    if(input=='2'){
      Serial.println(input);  //prints input to screen
      Serial.println("led1 goes high");
      digitalWrite(led1,HIGH);  //sets pin HIGH
      delay(2000);   
      digitalWrite(led2,LOW);    //sets pin LOW     
    }
    else if(input=='5'){
      Serial.println(input);  //prints input to screen
      Serial.println("led2 goes high");
      digitalWrite(led2,HIGH); //sets pin HIGH
      delay(2000);
      digitalWrite(led1,LOW); //sets pin LOW
    } 
    
  }
}
