/***************************************************************************************************************
FILE: HLC_Web.ino
PROJECT: HELIOSLIGHTCONTROL
MODULE: ESP 01 for Webinterfacing
Description: Its the Main File of the Web Moduke which sends Data to the Base Station.
                Makes an AccessPoint with SSID HLC-Web


Compiler dependencies or special instructions:
- ESP8266WiFi.h

REVISION HISTORY
Date: By: Description:
18.02.2019: Maximilian Klug: First Commit

****************************************************************************************************************/
#include <ESP8266WiFi.h>

const char* ssid = "HLC-Web";
const char* password = "12345678";

unsigned long ulReqcount;


// Create an instance of the server on Port 80
WiFiServer server(80);

void setup() 
{
  // setup globals
  ulReqcount=0; 

  // start serial
  Serial.begin(9600);
  delay(1);
  
  // AP mode
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  server.begin();
}

void loop() 
{ 
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) 
  {
    return;
  }
  
  // Wait until the client sends some data
  unsigned long ultimeout = millis()+250;
  while(!client.available() && (millis()<ultimeout) )
  {
    delay(1);
  }
  if(millis()>ultimeout) 
  { 
    return; 
  }
  
  // Read the first line of the request
  String sRequest = client.readStringUntil('\r');
  client.flush();
  
  // stop client, if request is empty
  if(sRequest=="")
  {
    client.stop();
    return;
  }
  
  // get path; end of path is either space or ?
  // Syntax is e.g. GET /?pin=MOTOR1STOP HTTP/1.1
  String sPath="",sParam="", sCmd="";
  String sGetstart="GET ";
  int iStart,iEndSpace,iEndQuest;
  iStart = sRequest.indexOf(sGetstart);
  if (iStart>=0)
  {
    iStart+=+sGetstart.length();
    iEndSpace = sRequest.indexOf(" ",iStart);
    iEndQuest = sRequest.indexOf("?",iStart);
    
    // are there parameters?
    if(iEndSpace>0)
    {
      if(iEndQuest>0)
      {
        // there are parameters
        sPath  = sRequest.substring(iStart,iEndQuest);
        sParam = sRequest.substring(iEndQuest,iEndSpace);
      }
      else
      {
        // NO parameters
        sPath  = sRequest.substring(iStart,iEndSpace);
      }
    }
  }
  
  ///////////////////////////////////////////////////////////////////////////////
  // output parameters to serial, you may connect e.g. an Arduino and react on it
  ///////////////////////////////////////////////////////////////////////////////
  if(sParam.length()>0)
  {
    int iEqu=sParam.indexOf("=");
    if(iEqu>=0)
    {
      sCmd = sParam.substring(iEqu+1,sParam.length());
      Serial.println(sCmd);
    }
  }
  
  ///////////////////////////
  // format the html response
  ///////////////////////////
  String sResponse,sHeader;
  
  ////////////////////////////
  // 404 for non-matching path
  ////////////////////////////
  if(sPath!="/")
  {
    sResponse="<html><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL was not found on this server.</p></body></html>";
    
    sHeader  = "HTTP/1.1 404 Not found\r\n";
    sHeader += "Content-Length: ";
    sHeader += sResponse.length();
    sHeader += "\r\n";
    sHeader += "Content-Type: text/html\r\n";
    sHeader += "Connection: close\r\n";
    sHeader += "\r\n";
  }
  ///////////////////////
  // format the html page
  ///////////////////////
  else
  {
    ulReqcount++;
    sResponse  = "<html><head><title>Steuerung f&uumlr Helios Light Control</title></head><body>";
    sResponse += "<font color=\"#000000\"><body bgcolor=\"#d0d0f0\">";
    sResponse += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=yes\">";
    sResponse += "<h1>teuerung f&uumlr Helios Light Control</h1>";
    sResponse += "<FONT SIZE=+2>";
        
    sResponse += "Matrix Control<BR>";
    sResponse += "<FONT SIZE=-1>";
    sResponse += "<p>Funktion FFT <a href=\"?pin=matrix_fft_ON\"><button>einschalten</button></a>&nbsp;<a href=\"?pin=matrix_fft_OFF\"><button>ausschalten</button></a></p>";
    sResponse += "<p>Funktion Temperaturverlauf <a href=\"?pin=matrix_temperaturverlauf_ON\"><button>einschalten</button></a>&nbsp;<a href=\"?pin=matrix_temperaturverlauf_OFF\"><button>ausschalten</button></a></p>";
    sResponse += "<p>Funktion Beleuchtung nach Temp. <a href=\"?pin=matrix_beleuchtungNachTemperatur_ON\"><button>einschalten</button></a>&nbsp;<a href=\"?pin=matrix_beleuchtungNachTemperatur_OFF\"><button>ausschalten</button></a></p>";
    sResponse += "<FONT SIZE=+1>";
    sResponse += "Lamp Control<BR>";
    sResponse += "<FONT SIZE=-1>";
    sResponse += "<p>Funktion Lampe <a href=\"?pin=lamp_ON\"><button>einschalten</button></a>&nbsp;<a href=\"?pin=lamp_OFF\"><button>ausschalten</button></a></p>";


    //////////////////////
    // react on parameters
    //////////////////////
    if (sCmd.length()>0)
    {
      // write received command to html page
      sResponse += "Kommando:" + sCmd + "<BR>";
      
      // switch GPIO
      if(sCmd.indexOf("FUNCTION1ON")>=0)
      {
        digitalWrite(2, 1);
      }
      else if(sCmd.indexOf("FUNCTION1OFF")>=0)
      {
        digitalWrite(2, 0);
      }
    }
    
    sResponse += "<FONT SIZE=-2>";
    sResponse += "<BR>Aufrufz&auml;hler="; 
    sResponse += ulReqcount;
    sResponse += "<BR>";
    sResponse += "Stefan Thesen 08/2015<BR>";
    sResponse += "</body></html>";
    
    sHeader  = "HTTP/1.1 200 OK\r\n";
    sHeader += "Content-Length: ";
    sHeader += sResponse.length();
    sHeader += "\r\n";
    sHeader += "Content-Type: text/html\r\n";
    sHeader += "Connection: close\r\n";
    sHeader += "\r\n";
  }
  
  // Send the response to the client
  client.print(sHeader);
  client.print(sResponse);
  
  // and stop the client
  client.stop();
}
