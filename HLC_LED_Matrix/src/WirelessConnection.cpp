#include "WirelessConnection.h"
#include <Arduino.h>

#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>

RF24 radio(7, 8);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network



WirelessConnection::WirelessConnection()
{
    // Initalizing List
    SPI.begin();
    radio.begin();
    network.begin(90, m_id);  //(channel, node address)
}

void WirelessConnection::sendData(Package data)
{
    data.sender = m_id;

    network.update();
    RF24NetworkHeader header(data.reciever);     // (Address where the data is going)
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