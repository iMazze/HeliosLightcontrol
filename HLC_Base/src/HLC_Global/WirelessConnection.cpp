/***************************************************************************************************************
FILE: WirelessConnection.cpp
PROJECT: HELIOSLIGHTCONTROL
MODULE: HLC_Global
Description:    There are the most functions for sending and recieving data over our 2.4Ghz protocoll.
                There is also a attach Interrupt method. 


Compiler dependencies or special instructions:
- Arduino.h

REVISION HISTORY
Date: By: Description:
23.02.19: Maximilian Klug: Made last comments
****************************************************************************************************************/
#include "WirelessConnection.h"
#include <Arduino.h>


// Constructor of Class WirelessConnection
// Radio: Created Radio 24 Instance from your main.ino FILE
// id: its the own unique id
WirelessConnection::WirelessConnection(RF24& _radio, uint64_t id)
    : radio(_radio)
{
    m_id = id;

}

// Starts the WirelessConnection in listening mode
void WirelessConnection::start()
{
    radio.setAutoAck(1);            // Ensure autoACK is enabled so rec sends ack packet to let you know it got the transmit packet payload
    radio.enableAckPayload();       //allows you to include payload on ack packet
    radio.setPALevel(RF24_PA_LOW);  //Set power level to low, won't work well at higher levels (interfer with receiver)
    radio.openReadingPipe(1, m_id); //open pipe o for recieving meassages with pipe address
    radio.startListening();         // Start listening for messages
}

// Attaches an interrupt function to the protocoll.
// The function is called if the module is recieving data
void WirelessConnection::attachInterruptFunction(void (* InterruptFunction)())
{
    //mask all IRQ triggers except for receive (1 is mask, 0 is no mask)
    radio.maskIRQ(1,1,0);               
    
    // Create interrupt
    // Parameters: PIN, the name of the interrupt function or ISR, and condition to trigger interrupt
    attachInterrupt(IRQ_PIN, InterruptFunction, FALLING);  
    
}

// Sends the package data to an specific reciever with the reciever_address
// It interrupts the recieving process and sends some data
void WirelessConnection::sendData(Package data, uint64_t reciever_address)
{
    Serial.println("Sending packet");
    data.source_id = m_id;
    
    //transmitter so stop listening for data
  	radio.stopListening();  

    // pipe address that we will communicate over, must be the same for each nRF24 module   
    radio.openWritingPipe(reciever_address);   
    
    //if the send fails let the user know over serial monitor     
	if (!radio.write( &data, sizeof(data) )){  
       Serial.println("packet delivery failed");  
  	}
  	
    // Start listening for messages
    radio.startListening(); 

}

// Reads the incoming data from the 2.4Ghz module
Package WirelessConnection::getData()
{
    Package data;

    //get data sent from transmit
    while(radio.available()) { 
        //read one package of data and store it in data variable
        radio.read(&data, sizeof(data)); 
    }

    return data;
}