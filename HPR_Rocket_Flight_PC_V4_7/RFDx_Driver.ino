
//#define radioPort Serial7
#define RADIO_UART_SPEED 57600


bool beginRFD900()
{


  boolean successFlag = true;

  //radioPort.begin(RADIO_UART_SPEED);


  if (successFlag)
  {
    Serial.println("RFD900 Radio OK!");
  }

  return true;
}

bool sendPktRFD900(uint8_t *data1, uint8_t len)
{
  // for (int i = 0; i < len; i++)
  // {
  //   radioPort.write(data[i]);
  //   radioPort.flush();
  // }
  // radioPort.println();
  // radioPort.flush();
  //radioPort.println(data);
  // set flag
  radioFnctn = TXmode;
  TX = true;
  return true;
}
