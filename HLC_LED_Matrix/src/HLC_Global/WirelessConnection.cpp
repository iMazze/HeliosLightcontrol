#include "WirelessConnection.h"
#include <Arduino.h>

#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>

RF24 radio(CE_PIN, CSN_PIN);     // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network



WirelessConnection::WirelessConnection(uint64_t id)
{
    m_id = id;

    // Initalizing List
    SPI.begin();
    radio.begin();
    network.begin(90, m_id);  //(channel, node address)
}


void WirelessConnection::enableInterrupt()
{
    radio.setAutoAck(1);                    // Ensure autoACK is enabled so rec sends ack packet to let you know it got the transmit packet payload
    radio.enableAckPayload();         //allows you to include payload on ack packet
    radio.maskIRQ(1,1,0);               //mask all IRQ triggers except for receive (1 is mask, 0 is no mask)
    radio.setPALevel(RF24_PA_LOW); //Set power level to low, won't work well at higher levels (interfer with receiver)
    radio.openReadingPipe(1, m_id);      //open pipe o for recieving meassages with pipe address
    radio.startListening();                 // Start listening for messages
    attachInterrupt(IRQ_PIN, recieve_interrupt, FALLING);  //Create interrupt: 0 for pin 2 or 1 for pin 3, the name of the interrupt function or ISR, and condition to trigger interrupt
}

void WirelessConnection::sendData(Package data, uint16_t reciever_address)
{
    data.source_id = m_id;

    network.update();
    RF24NetworkHeader header(reciever_address);     // (Address where the data is going)
    bool ok = network.write(header, &data,sizeof(data)); // Send the data
}

Package WirelessConnection::getData()
{
    Package data;
    network.update();
    while ( network.available() ) {     // Is there any incoming data?
        RF24NetworkHeader header;
        network.read(header, &data, sizeof(data)); // Read the incoming data
    }

    return data;
}

Package WirelessConnection::getDataWithFilter(uint16_t filter_id)
{
    Package data;

    network.update();
    while ( network.available() ) {     // Is there any incoming data?
        RF24NetworkHeader header;
        network.read(header, &data, sizeof(data)); // Read the incoming data
        if (header.from_node == 0) {    // If data comes from Node 02
            return data;
        } else {    // If data comes from Node 012
            //return NULL;
            //error
            return data; // only for compiling well
        }
    }
}

//This is the function called when the interrupt occurs (pin 2 goes high)
//this is often referred to as the interrupt service routine or ISR
//This cannot take any input arguments or return anything
void static WirelessConnection::recieve_interrupt()
{
    //count++; //up the receive counter
    //while(wirelessSPI.available()) { //get data sent from transmit
    //    wirelessSPI.read( &gotByte, 1 ); //read one byte of data and store it in gotByte variable
    //}
}