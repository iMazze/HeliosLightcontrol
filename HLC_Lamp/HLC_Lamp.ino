/***************************************************************************************************************
FILE: 
PROJECT: HELIOSLIGHTCONTROL
MODULE: 
Description:


Compiler dependencies or special instructions:

REVISION HISTORY
Date: By: Description:
****************************************************************************************************************/



#include <ESP8266WiFi.h>
const char* ssid     = "Villa Impuls 7.6 EG";      // SSID
const char* password = "Freude888";      // Password
const char* host = "xxx.xxx.xxx.xxx";  // Server IP
const int   port = 8080;            // Server Port
const int   watchdog = 5000;        // Watchdog frequency
unsigned long previousMillis = millis(); 




void setup() {





  
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}




//  Hue constants
 
const char hueHubIP[] = "192.168.42.177";  // Hue hub IP
const char hueUsername[] = "zFp1pECECADeWldLrlR5CR6bjCxtHKLPoT9nvfdC";  // Hue username
const int hueHubPort = 80;

// PIR
int pir = 2;
boolean activated = false;

//  Hue variables
boolean hueOn;  // on/off
int hueBri;  // brightness value
long hueHue;  // hue value
String hueCmd;  // Hue command

unsigned long buffer=0;  //buffer for received data storage
unsigned long addr;


WiFiClient client;

int kelvin = 2700;
uint8_t data;

void loop() 
{
    if(digitalRead(pir) == 1){
    Serial.println("activated");

    
data = Serial.read();  
  

  Serial.println(data);
  kelvin = data;
delay(200);


// Test der Funktion zum einstellen der Farbtemperatur
//int kelvin = 2700;

 String command ="{\"on\":true, \"ct\":";
    String variable = String(kelvin);
    String command_end = "}";
    String command2 = command + variable + command_end;
    setHue(1,command2);
    setHue(2,command2);
    setHue(3,command2);
    delay(300);


//setColorTemperature(kelvin);


// Test der Funktion zum einstellen der Lichtfarbe
char color = 'b';
unsigned int lightNum = 1;

//setColor( color, lightNum);





  
    // so we can track state
    activated = true;
  }
  else{

    
      activated = false;
      Serial.println("deactivated");
      
      //was activated, so send a single off command
      String command = "{\"on\": false}";
      setHue(1,command);
      setHue(2,command);
      setHue(3,command);
     
  }
  
}

/* setHue() is our main command function, which needs to be passed a light number and a 
 * properly formatted command string in JSON format (basically a Javascript style array of variables
 * and values. It then makes a simple HTTP PUT request to the Bridge at the IP specified at the start.
 */
boolean setHue(int lightNum,String command)
{
  if (client.connect(hueHubIP, hueHubPort))
  {
    while (client.connected())
    {
      client.print("PUT /api/");
      client.print(hueUsername);
      client.print("/lights/");
      client.print(lightNum);  // hueLight zero based, add 1
      client.println("/state HTTP/1.1");
      client.println("keep-alive");
      client.print("Host: ");
      client.println(hueHubIP);
      client.print("Content-Length: ");
      client.println(command.length());
      client.println("Content-Type: text/plain;charset=UTF-8");
      client.println();  // blank line before body
      client.println(command);  // Hue command
    }
    client.stop();
    return true;  // command executed
  }
  else
    return false;  // command failed
}






/////////////////////////////////////////////////////////////////////////////
// Funktion zum aendern der Farbe der Hue Lampen
/////////////////////////////////////////////////////////////////////////////

void setColor(char color, unsigned int lightNum)
{
  
   if(digitalRead(pir) == 1){
    Serial.println("activated");
String command;


switch (color) {
  case 'r':
    command = "{\"on\":true, \"xy\":[0.7, 0.25]}";
    break;
  case 'b':
    command = "{\"on\":true, \"xy\":[0.17, 0.05]}";
    break;
  case 'g':
    command = "{\"on\":true, \"xy\":[0.27, 0.6]}";
    break;
   case 'y':
  command = "{\"on\":true, \"xy\":[0.47, 0.45]}";
    break; 
    
  default:
    // statements
    break;
}


    setHue(lightNum,command);
   
    delay(300);


  
    // so we can track state
    activated = true;
  }

  

  
  }


/////////////////////////////////////////////////////////////////////////////
// Funktion zum aendern der Lichttemperatur der Hue Lampen
/////////////////////////////////////////////////////////////////////////////

void setColorTemperature(int kelvin)
{
  
  
   if(digitalRead(pir) == 1){
    Serial.println("activated");

float ct;

// Formel zum berechnen des ct Werts aus dem Kelvin Wert
ct = 0.000005 *kelvin*kelvin -0.0967 * kelvin + 588.12;

//ct = 500 -((kelvin-1700):24)

    String command ="{\"on\":true, \"ct\":";
    String variable = String(ct);
    String command_end = "}";
    String command2 = command + variable + command_end;
    setHue(1,command2);
    setHue(2,command2);
    setHue(3,command2);
    delay(300);


  
    // so we can track state
    activated = true;
  }
 
  
  }






  /* A helper function in case your logic depends on the current state of the light. 
 * This sets a number of global variables which you can check to find out if a light is currently on or not
 * and the hue etc. Not needed just to send out commands
 */
boolean getHue(int lightNum)
{
  if (client.connect(hueHubIP, hueHubPort))
  {
    client.print("GET /api/");
    client.print(hueUsername);
    client.print("/lights/");
    client.print(lightNum);  
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(hueHubIP);
    client.println("Content-type: application/json");
    client.println("keep-alive");
    client.println();
    while (client.connected())
    {
      if (client.available())
      {
        client.findUntil("\"on\":", "\0");
        hueOn = (client.readStringUntil(',') == "true");  // if light is on, set variable to true
 
        client.findUntil("\"bri\":", "\0");
        hueBri = client.readStringUntil(',').toInt();  // set variable to brightness value
 
        client.findUntil("\"hue\":", "\0");
        hueHue = client.readStringUntil(',').toInt();  // set variable to hue value
        
        break;  // not capturing other light attributes yet
      }
    }
    client.stop();
    return true;  // captured on,bri,hue
  }
  else
    return false;  // error reading on,bri,hue
}