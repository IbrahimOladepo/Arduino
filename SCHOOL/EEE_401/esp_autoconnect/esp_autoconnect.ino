#include <SoftwareSerial.h>

#define rxPin 10
#define txPin 11

//SSID + KEY
const char SSID_ESP[] = "InnJooOne";
const char SSID_KEY[] = "12345678";

//MODES
const char CWMODE = '1';//CWMODE 1=STATION, 2=APMODE, 3=BOTH
const char CIPMUX = '1';//CWMODE 0=Single Connection, 1=Multiple Connections

SoftwareSerial esper(rxPin, txPin);// rx tx

//DEFINE ALL GLOBAL VAARIABLES HERE
unsigned long timeout_start_val;
char scratch_data_from_ESP[20];//first byte is the length of bytes
char payload[150];
byte payload_size=0, counter=0;
char ip_address[16];
char youtube_subs[10];
char youtube_views[13];
char current_temp[5];
char hi_temp[5];
char lo_temp[5];

//DEFINE KEYWORDS HERE
const char keyword_OK[] = "OK";
const char keyword_Ready[] = "Ready";
const char keyword_no_change[] = "no change";
const char keyword_blank[] = "#&";
const char keyword_ip[] = "192.";
const char keyword_rn[] = "\r\n";
const char keyword_quote[] = "\"";
const char keyword_carrot[] = ">";
const char keyword_sendok[] = "SEND OK";
const char keyword_linkdisc[] = "Unlink";

void setup() {
  // put your setup code here, to run once:
  esper.begin(9600);//default baudrate for ESP
  // esper.listen();//not needed unless using other software serial instances
  Serial.begin(115200); //for status and debug
  delay(5000);//delay before kicking things off
  
  setup_ESP();//go setup the ESP 
}

void loop() {
  // put your main code here, to run repeatedly:

}


boolean setup_ESP(){//returns a '1' if successful
  
  esper.print("AT\r\n");// Send just 'AT' to make sure the ESP is responding
  //this read_until_... function is used to find a keyword in the ESP response - more on this later and in the function itself
  if(read_until_ESP(keyword_OK,sizeof(keyword_OK),5000,0))//go look for keyword "OK" with a 5sec timeout
    Serial.println("ESP CHECK OK");
  else
    Serial.println("ESP CHECK FAILED");
    
  serial_dump_ESP();//this just reads everything in the buffer and what's still coming from the ESP

  esper.print("AT+RST\r\n");// Give it a reset - who knows what condition it was in, better to start fresh
  
  if(read_until_ESP(keyword_Ready,sizeof(keyword_Ready),5000,0))//go look for keyword "Ready" - takes a few seconds longer to complete
    Serial.println("ESP RESET OK");//depneding on the FW version on the ESP, sometimes the Ready is with a lowercase r - ready
  else
    Serial.println("ESP RESET FAILED");
    
  serial_dump_ESP();
  
   esper.print("AT+CWMODE=");// set the CWMODE
   esper.print(CWMODE);//just send what is set in the constant
   esper.print("\r\n");
  if(read_until_ESP(keyword_OK,sizeof(keyword_OK),1000,0))//go look for keyword "OK"
    Serial.println("ESP CWMODE SET");
  else
    Serial.println("ESP CWMODE SET FAILED"); //probably going to fail, since a 'no change' is returned if already set - would be nice to check for two words
  
  serial_dump_ESP();  
   
   //Here's where the SSID and PW are set
   esper.print("AT+CWJAP=\"");// set the SSID AT+CWJAP="SSID","PW"
   esper.print(SSID_ESP);//from constant 
   esper.print("\",\"");
   esper.print(SSID_KEY);//form constant
   esper.print("\"\r\n");
  if(read_until_ESP(keyword_OK,sizeof(keyword_OK),10000,0))//go look for keyword "OK"
    Serial.println("ESP SSID SET OK");
  else
    Serial.println("ESP SSID SET FAILED");   
  serial_dump_ESP();
  
  //This checks for and stores the IP address
  Serial.println("CHECKING FOR AN IP ADDRESS");
  esper.print("AT+CIFSR\r\n");//command to retrieve IP address from ESP
  if(read_until_ESP(keyword_rn,sizeof(keyword_rn),10000,0)){//look for first \r\n after AT+CIFSR echo - note mode is '0', the ip address is right after this
  if(read_until_ESP(keyword_rn,sizeof(keyword_rn),1000,1)){//look for second \r\n, and store everything it receives, mode='1'
    //store the ip adress in its variable, ip_address[]
    for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_rn)+1); i++)//that i<=... is going to take some explaining, see next lines
       ip_address[i] = scratch_data_from_ESP[i];//fill up ip_address with the scratch data received
//i=1 because i=0 is the length of the data found between the two keywords, BUT this includes the length of the second keyword, so i<= to the length minus
//size of teh keyword, but remember, sizeof() will return one extra, which is going to be subtracted, so I just added it back in +1
    ip_address[0] = (scratch_data_from_ESP[0]-sizeof(keyword_rn)+1);//store the length of ip_address in [0], same thing as before
    Serial.print("IP ADDRESS = ");//print it off to verify
    for(int i=1; i<=ip_address[0]; i++)//send out the ip address
    Serial.print(ip_address[i]);
    Serial.println("");
  }}//if first \r\n
  else
  Serial.print("IP ADDRESS FAIL");
  serial_dump_ESP();
  
  esper.print("AT+CIPMUX=");// set the CIPMUX
  esper.print(CIPMUX);//from constant
  esper.print("\r\n");
  
  if(read_until_ESP(keyword_OK,sizeof(keyword_OK),5000,0))//go look for keyword "OK" or "no change
    Serial.println("ESP CIPMUX SET");
  else
    Serial.println("ESP CIPMUX SET FAILED"); 
  serial_dump_ESP();
 
  //that's it!  Could be done by nesting everything together, so if one thing fails, it returns '0', and if it gets all the way through it returns '1'...oh well
  
}//setup ESP


void serial_dump_ESP(){
  char temp;
  
  while(esper.available()){
    temp =esper.read();
    delay(1);//could play around with this value if buffer overflows are occuring
  }//while
}//serial dump


boolean read_until_ESP(const char keyword1[], int key_size, int timeout_val, byte mode){
  timeout_start_val=millis();//for the timeout
  char data_in[20];//this is the buffer - if keyword is longer than 20, then increase this
  int scratch_length=1;//the length of the scratch data array
  key_size--;//since we're going to get an extra charachter from the sizeof()
 
 //FILL UP THE BUFFER
 for(byte i=0; i<key_size; i++){//we only need a buffer as long as the keyword
  
            //timing control
            while(!esper.available()){//wait until a new byte is sent down from the ESP - good way to keep in lock-step with the serial port
              if((millis()-timeout_start_val)>timeout_val){//if nothing happens within the timeout period, get out of here
                Serial.println("timeout");
                return 0;//this will end the function
              }//timeout
            }// while !avail
   
    data_in[i]=esper.read();// save the byte to the buffer 'data_in[]

    if(mode==1){//this will save all of the data to the scratch_data_from
      scratch_data_from_ESP[scratch_length]=data_in[i];//starts at 1
      scratch_data_from_ESP[0]=scratch_length;// [0] is used to hold the length of the array
      scratch_length++;//increment the length
    }//mode 1
    
  }//for i
  
//THE BUFFER IS FULL, SO START ROLLING NEW DATA IN AND OLD DATA OUT
  while(1){//stay in here until the keyword found or a timeout occurs

     //run through the entire buffer and look for the keyword
     //this check is here, just in case the first thing out of the ESP was the keyword, meaning the buffer was actually filled with the keyword
     for(byte i=0; i<key_size; i++){
       if(keyword1[i]!=data_in[i])//if it doesn't match, break out of the search now
       break;//get outta here
       if(i==(key_size-1)){//we got all the way through the keyword without breaking, must be a match!
       return 1; //return a 1 and get outta here!
       }//if
     }//for byte i
     
    //start rolling the buffer
    for(byte i=0; i<(key_size-1); i++){// keysize-1 because everthing is shifted over - see next line
      data_in[i]=data_in[i+1];// so the data at 0 becomes the data at 1, and so on.... the last value is where we'll put the new data
    }//for
          
           //timing control
            while(!esper.available()){// same thing as done in the buffer
              if((millis()-timeout_start_val)>timeout_val){
                Serial.println("timeout");
                return 0;
              }//timeout
            }// while !avail

    data_in[key_size-1]=esper.read();//save the new data in the last position in the buffer
   
    if(mode==1){//continue to save everything if thsi is set
      scratch_data_from_ESP[scratch_length]=data_in[key_size-1];
      scratch_data_from_ESP[0]=scratch_length;
      scratch_length++;
    }//mode 1
    
  }//while 1
}//read until ESP
