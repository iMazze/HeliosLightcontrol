/***************************************************************************************************************
FILE: 
PROJECT: HELIOSLIGHTCONTROL
MODULE: 
Description:


Compiler dependencies or special instructions:

REVISION HISTORY
Date: By: Description:
****************************************************************************************************************/
#include "WirelessConnection.h"
#include <Arduino.h>


//RF24Network network(radio);      // Include the radio in the network



WirelessConnection::WirelessConnection(RF24& _radio, uint64_t id)
    : radio(_radio)
{
    m_id = id;

}

void WirelessConnection::start()
{
    radio.setAutoAck(1);                    // Ensure autoACK is enabled so rec sends ack packet to let you know it got the transmit packet payload
    radio.enableAckPayload();         //allows you to include payload on ack packet
    radio.setPALevel(RF24_PA_LOW); //Set power level to low, won't work well at higher levels (interfer with receiver)
    radio.openReadingPipe(1, m_id);      //open pipe o for recieving meassages with pipe address
    radio.startListening();                 // Start listening for messages


  



}


void WirelessConnection::attachInterruptFunction(void (* InterruptFunction)())
{
    radio.maskIRQ(1,1,0);               //mask all IRQ triggers except for receive (1 is mask, 0 is no mask)
    
    //Create interrupt: 0 for pin 2 or 1 for pin 3, the name of the interrupt function or ISR, and condition to trigger interrupt
    attachInterrupt(IRQ_PIN, InterruptFunction, FALLING);  
    
}

void WirelessConnection::sendData(Package data, uint64_t reciever_address)
{
    data.source_id = m_id;
    
    Serial.println("Sending packet"); 
  	radio.stopListening();        //transmitter so stop listening for data
    radio.openWritingPipe(reciever_address);        // pipe address that we will communicate over, must be the same for each nRF24 module
	if (!radio.write( &data, sizeof(data) )){  //if the send fails let the user know over serial monitor
       Serial.println("packet delivery failed");  
  	}
  	
    radio.startListening();                 // Start listening for messages

}


Package WirelessConnection::getData()
{
    Package data;

    while(radio.available()) { //get data sent from transmit
       radio.read( &data, sizeof(data) ); //read one byte of data and store it in gotByte variable
    }

    return data;
}