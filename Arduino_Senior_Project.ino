#include <SPI.h>

#include <Ethernet.h>



// MAC address and IP address for your controller

// MAC=90 a2 da 0d 14 dc

byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0x14, 0xDC };

//IPAddress ip(192,168,1, 3);



// Initialize the Ethernet server library with port 80

EthernetServer server(80);



//set the pins in use

int pins[]={46,48,49,47,45,43,41,39};

int const NUM_OF_PINS=8;



//delay between setting the bit sequence returning to normal state, 0.

int const TRANSITION_DELAY=125;  // delay between the shorts 

int const TRANSITION_DELAY_INSTRUCTIONS=125;  // Delay Between instructions

int const DELAY_START=1000; // Delay before executing the start button

//Index at which the bit sequence in the http request start

int const BITSEQ_INDEX=6; // send the request you have to start at #6, 6 characters that you have to start parsing from there



void setup() {

 //Open serial communications

 Serial.begin(9600);

 //setup the pins as output

 for(int i=0;i<NUM_OF_PINS;i++){

   pinMode(pins[i], OUTPUT);

 }

 //Initializes the ethernet library and network settings
Serial.print("Configuring IP...");
 if(Ethernet.begin(mac) == 0){
    Serial.println("Failed to configure");
     while(true); 
 }
 else
   Serial.println("complete");

 //start the server at port 80

 server.begin();

}



void loop(){

  //get a client connected to Arduino server. If there isnt any, then client==false

  EthernetClient client = server.available();

  //Serial.println("Checking for clients...");

  boolean currentLineIsBlank = true;

  if (client) {

    char c;

    String s;

    while (client.connected()) {

      if (client.available()) {  //determine if there is >0 bytes to process from this client

          c = client.read();

          s+=String(c);

         if (c == '\n' && currentLineIsBlank) {

           //reply(client,s); //to see the Reply in the web page

           break;

         }

         if (c == '\n') {

          // you're starting a new line

          currentLineIsBlank = true;

        }

        else 

         if (c != '\r') {

          // you've gotten a character on the current line

          currentLineIsBlank = false;

         }

      }

    }

    client.stop();

    Serial.println("Executing Instructions");

    parse_exec(s,BITSEQ_INDEX);

    Serial.println("Done");

  }

}



void reply(EthernetClient client,String s){

  client.println("HTTP/1.1 200 OK");

  client.println("Content-Type: text/html");

  client.println("Connnection: close");

  client.println();

  client.println("<html><head></head><body><div>");

  client.println(s);

  client.println("</div></body></html>");

}



//parse and execute the sequence of instructions

void parse_exec(String ar,int cnt){

 int size=CharToInt(ar.charAt(cnt++));

 String ins;

 for(int i=0;i<size;i++){

   ins=ar.substring(cnt,cnt+2);
	if(ins=="18"){
		delay(DELAY_START);
	}
	exec(ins);
		
   delay(TRANSITION_DELAY_INSTRUCTIONS);
   cnt=cnt+2;

 }

}



void exec(String in){

 int pin1=CharToInt(in.charAt(0));

 int pin2=CharToInt(in.charAt(1));

 if (pin1>8 or pin1<1 or pin2>8 or pin2<1){

	Serial.println('Error: pin number out of range');

 }

 else{

     pin1-=1;

     pin2-=1;

     digitalWrite(pins[pin1], HIGH);

     digitalWrite(pins[pin2], HIGH);

     delay(TRANSITION_DELAY);

     digitalWrite(pins[pin1], LOW);

     digitalWrite(pins[pin2], LOW);

 }

}



int CharToInt(const char c){

    switch (c)

    {

    case '0':

        return 0;

    case '1':

        return 1;

    case '2':

        return 2;

    case '3':

        return 3;

    case '4':

        return 4;

    case '5':

        return 5;

    case '6':

        return 6;

    case '7':

        return 7;

    case '8':

        return 8;

    case '9':

        return 9;

    default:

	Serial.println("Error: Its not a number. Reason:the number of instructions is wrong or instructions contain characteres.");return -1;

    }

}



void test(){

 Serial.println("Testing Pins in use...");

 for(int i=0;i<8;i++){

   digitalWrite(pins[i], HIGH);

 }

 delay(1000);

 for(int i=0;i<8;i++){

    digitalWrite(pins[i], LOW);

 }

 delay(1000);

}
