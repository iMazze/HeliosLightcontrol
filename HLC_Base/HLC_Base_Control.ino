/*========================================================================*/
/*                            Handles                                     */
/*========================================================================*/
void handleStaticModes()
{
    if(!isRoomEmpty)
    {
        // Handle HLC_LED_Matrix
        switch(matrixMode)
        {
            case off: 
            {
                matrixSetOff();
            }
            break;
            case fft:
            {
                matrixSetFFT();
            }
            break;
            case temperaturverlauf:
            {
                matrixSetTemperatureChart();
            }
            break;
        }

        // Handle HLC_Lamp
        if(lampOn)
        {
            // Luftfeuchtigkeit über 60 % orange aufleuchten unter 40 % Lila aufleuchten
            if(pckBuff.hasPackageWithId(MSG_ID::Sensor_Humidity))
            {
                uint16_t actHumidity = pckBuff.getPackageWithId(MSG_ID::Sensor_Humidity).data_0;
                if(actHumidity > 60)
                {
                    lampSendBlink(0xFF, 0xFF, 0); // Orange
                }
                else if(actHumidity < 40)
                {
                    lampSendBlink(0, 0, 0xFF); // Lila
                }
            }
        }
        else
        {
            lampSetOff();
        }
        
    }
}

void handleNewRecieve()
{
    if(!isRoomEmpty)
    {
        // Handle HLC_LED_Matrix
        switch(matrixMode)
        {
            case beleuchtungNachTemperatur: 
            {
                // If there is no package --> break;
                if(!pckBuff.hasPackageWithId(MSG_ID::Sensor_Temperature))
                {
                    break;
                }
                uint16_t actTemperature = pckBuff.getPackageWithId(MSG_ID::Sensor_Temperature).data_0;
                if(actTemperature>50)
                {
                    matrixSendHEX(0xFF0000);
                }
                else if(actTemperature>40)
                {
                    matrixSendHEX(0x00FFFF);
                }
                else if(actTemperature>35)
                {
                    matrixSendHEX(0x7F00FF);
                }
                else if(actTemperature>30)
                {
                    matrixSendHEX(0xFF00FF);
                }
                else if(actTemperature>25)
                {
                    matrixSendHEX(0x808080);
                }
                else if(actTemperature>20)
                {
                    matrixSendHEX(0xFFCCE5);
                }
                else
                {
                    matrixSendHEX(0xFFFFFF);
                }
            }
            break;
        }

        // Handle HLC_Lamp
        if(lampOn)
        {
            // If there is no package --> break;
            if(pckBuff.hasPackageWithId(MSG_ID::Sensor_Colortemp))
            {
                uint16_t actColorTemperature = pckBuff.getPackageWithId(MSG_ID::Sensor_Colortemp).data_0;
                lampSendColorTemperature(actColorTemperature);
            }
        }
    }
    else
    {
        matrixSetOff();
        lampSetOff();
    }
    
}

/*========================================================================*/
/*                          Matrix Controls                               */
/*========================================================================*/
void matrixSetOff()
{
  Package p;
  p.id = MSG_ID::Matrix_RGB;
  p.data_0 = 0;
  wc.sendData(p, ID_HLC_MATRIX);
}

void matrixSendHSV(int val)
{
  Package p;
  p.id = MSG_ID::Matrix_HSV;
  p.data_0 = 1;
  p.data_1 = val;
  p.data_2 = 250;
  p.data_3 = 100;
  wc.sendData(p, ID_HLC_MATRIX);
}

void matrixSendHEX(unsigned long rgb)
{  
    //   int red, green,blue;
    //   red = rgb >> 16 ;
    
    //   green = (rgb & 0x00ff00) >> 8;
    
    //   blue = (rgb & 0x0000ff);
    
    //   rgb = 0;
    
    //   rgb |= red <<16;
    //   rgb |= blue <<8;
    //   rgb |=green;
  
    Package p;
    p.id = MSG_ID::Matrix_HEX;
    p.data_0 = 1;
    //   p.data_1 = red*0.2f;
    //   p.data_2 = green*0.2f;
    //   p.data_3 = blue*0.2f;
    p.data_1 = rgb;
    wc.sendData(p, ID_HLC_MATRIX);
}

void matrixSetFFT()
{
    Package p;
    p.id = MSG_ID::Matrix_FFT_Show;
    p.data_0 = 1;
    wc.sendData(p, ID_HLC_MATRIX);
}

void matrixSetTemperatureChart()
{
    Package p;
    p.id = MSG_ID::Matrix_Tempchart_Show;
    p.data_0 = 1;
    wc.sendData(p, ID_HLC_MATRIX);
}

void matrixSendTemperature(int temperature)
{
  Serial.println("Send Temperature");
  Package p;
  p.id = MSG_ID::Matrix_AddTempValue;
  p.data_0 = temperature;//random(10,40);
  wc.sendData(p, ID_HLC_MATRIX);
  d.logPackage(p);
}

/*========================================================================*/
/*                           Lamp Controls                                */
/*========================================================================*/

void lampSetOff()
{
  Package p;
  p.id = MSG_ID::Lamp_Colortemp;
  p.data_0 = 0;
  wc.sendData(p, ID_HLC_LAMP);
}

void lampSendColorTemperature(int colorTemperature)
{
  Package p;
  p.id = MSG_ID::Lamp_Colortemp;
  p.data_0 = 1; // Steady 1
  p.data_1 = colorTemperature;
  wc.sendData(p, ID_HLC_LAMP);
  d.logPackage(p);
}

void lampSendBlink(uigt r, uint8_t g, uint8_t b)
{
    Package p;
    p.id = MSG_ID::Lamp_Blink;
    p.data_0 = 1; // Steady 1
    p.data_1 = r;
    p.data_2 = g;
    p.data_3 = b;
    wc.sendData(p, ID_HLC_LAMP);
    d.logPackage(p);
}