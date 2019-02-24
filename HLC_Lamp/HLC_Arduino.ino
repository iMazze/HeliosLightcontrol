#include "src/HLC_Global/WirelessConnection.h"


void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);

    // Setup RF24
    radio_24.begin();


    // Setup WirelessConnection
    wc.attachInterruptFunction(nrf_interrupt);
    wc.start();


}


void nrf_interrupt()
{
    
    Package p = wc.getData();
    d.logPackage(p);

    //Adds the recieved package to the Buffer
    pckBuff.addPackage(p);
}


int kelvin = 1700;
int counter = 100;

void loop() {

//String command1 ="\"<";
//String command2 = String(kelvin);
//String command3 =">\"";
//String command4 = command1 + command2 + command3;

if(pckBuff.hasPackages())
        {
            Package p = pckBuff.returnFirstPackage();
        }


kelvin=p.data_0;


Serial.print(kelvin);

   delay(5000);

 if (kelvin > 7000 || kelvin < 1700)
 {
  counter = (-1)* counter;
  
  }

}