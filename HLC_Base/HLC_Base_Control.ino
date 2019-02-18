void handleNewRecieve()
{
  switch(matrixMode)
  {
    case off: matrixSetOff();
    break;
    case beleuchtung: 
    {
      if(pckBuff.getPackageWithId(MSG_ID::Sensor_Temperature).data_0>50)
      {
        sendHEX(0xFF0000);
      }
      else if(pckBuff.getPackageWithId(MSG_ID::Sensor_Temperature).data_0>40)
      {
        sendHEX(0x00FFFF);
      }
      else if(pckBuff.getPackageWithId(MSG_ID::Sensor_Temperature).data_0>35)
      {
        sendHEX(0x7F00FF);
      }
      else if(pckBuff.getPackageWithId(MSG_ID::Sensor_Temperature).data_0>30)
      {
        sendHEX(0xFF00FF);
      }
      else if(pckBuff.getPackageWithId(MSG_ID::Sensor_Temperature).data_0>25)
      {
        sendHEX(0x808080);
      }
      else if(pckBuff.getPackageWithId(MSG_ID::Sensor_Temperature).data_0>20)
      {
        sendHEX(0xFFCCE5);
      }
      else
      {
        sendHEX(0xFFFFFF);
      }
    }
    break;
    case zutrittskontrolle: break;
  }
}

/*******************************************************
Marix Controls
********************************************************/
void matrixSetOff()
{
  Package p;
  p.id = MSG_ID::Matrix_RGB;
  p.data_0 = 0;
  wc.sendData(p, 0xB00B1E5000LL);
}

void sendHSV(int val)
{
  Package p;
  p.id = MSG_ID::Matrix_HSV;
  p.data_0 = 1;
  p.data_1 = val;
  p.data_2 = 250;
  p.data_3 = 100;
  wc.sendData(p, 0xB00B1E5000LL);
}

void sendHEX(unsigned long rgb)
{  
  int red, green,blue;
  red = rgb >> 16 ;
  
  green = (rgb & 0x00ff00) >> 8;
  
  blue = (rgb & 0x0000ff);
  
  rgb = 0;
  
  rgb |= red <<16;
  rgb |= blue <<8;
  rgb |=green;
  
  Package p;
  p.id = MSG_ID::Matrix_RGB;
  p.data_0 = 1;
  p.data_1 = red*0.2f;
  p.data_2 = green*0.2f;
  p.data_3 = blue*0.2f;
  wc.sendData(p, 0xB00B1E5000LL);
}
