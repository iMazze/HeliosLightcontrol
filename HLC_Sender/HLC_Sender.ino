#include <nRF24L01.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/
#include <RF24.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/

const int pinCE = 9; //This pin is used to set the nRF24 to standby (0) or active mode (1)
const int pinCSN = 10; //This pin is used to tell the nRF24 whether the SPI communication is a command or message to send out
byte counter = 1; //used to count the packets sent
RF24 wirelessSPI(pinCE, pinCSN); // Create your nRF24 object or wireless SPI connection
const uint64_t pAddress = 0xB00B1E5000LL;              // Radio pipe addresses for the 2 nodes to communicate.
#define SwitchPin 8 // Arcade switch is connected to Pin 8 on NANO



enum MSG_ID
{
    EMPTY = 0,
    Temperatur = 11,
    Luftfeuchte = 12,
    Farbtemperatur = 13,
    Helligkeit = 14,
    Matrix_FFT_Show = 20,
    Matrix_Fullon = 21,
    Matrix_RGB = 22,
    Matrix_HSV = 23
};

struct package
{
    MSG_ID id = MSG_ID::EMPTY;
    uint64_t source_id = 00;
    uint16_t data_0;
    uint16_t data_1;
    uint16_t data_2;
    uint16_t data_3;
};

typedef struct package Package;



void setup()  
{
  Serial.begin(57600);   //start serial to communicate process
  wirelessSPI.begin();            //Start the nRF24 module
  wirelessSPI.setAutoAck(1);                    // Ensure autoACK is enabled so rec sends ack packet to let you know it got the transmit packet payload
  wirelessSPI.enableAckPayload();               // Allow optional ack payloads
  wirelessSPI.setPALevel(RF24_PA_LOW);
  wirelessSPI.openWritingPipe(pAddress);        // pipe address that we will communicate over, must be the same for each nRF24 module
  wirelessSPI.stopListening();        //transmitter so stop listening for data
  randomSeed(analogRead(0));    //use random ADC value to seed random number algorithm
  
  pinMode(SwitchPin, INPUT_PULLUP); // Define the arcade switch NANO pin as an Input using Internal Pullups
  digitalWrite(SwitchPin,HIGH); // Set Pin to HIGH at beginning

}

void loop() {
  delay(50); //Generate delay time between 100msec and 5 sec
  

   if (digitalRead(SwitchPin) == LOW){ // If Switch is Activated
        Serial.println("Sending packet");
        Package p;
        p.id = MSG_ID::Matrix_HSV;
        p.data_0 = 1;
        p.data_1 = 120;
        p.data_2 = 100;
        p.data_3 = 100;

        if (!wirelessSPI.write( &p, sizeof(p) )){  //if the send fails let the user know over serial monitor
            Serial.println("packet delivery failed");  
        }
        Serial.println();   
        delay(500);
   }
   else {
    }

   counter++;
}