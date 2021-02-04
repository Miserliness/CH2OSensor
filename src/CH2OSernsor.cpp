#include "uartIDF.h"
#include "CH2OSensor.h"

/* UART */
int uart_num = UART_NUM_2;

char getConcCommand[] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
char switchToQAModeCommand[] = {0xFF, 0x01, 0x78, 0x41, 0x00, 0x00, 0x00, 0x00, 0x46};

UartIDF uartDevice;

CH2OSensor::CH2OSensor(){};

CH2OSensor::~CH2OSensor(){};

void CH2OSensor::init(int txPin, int rxPin, int baudrate, int uart_number)
{
  uartDevice.uartInitDevice(txPin, rxPin, 115200, uart_num, UART_DATA_8_BITS, UART_STOP_BITS_1);
}

char *CH2OSensor::sendData(char *comm)
{
  uartDevice.write(comm, 9);
  _res = uartDevice.read();
}

bool CH2OSensor::checkSum()
{
  char sRCalc = 0;
  for (int j = 0; j < 8; j++)
  {
    sRCalc += _res[j];
  }
  sRCalc = (~sRCalc);
  char sRCom = _res[8];
  if (sRCom == sRCalc)
  {
    return true;
  }
  return false;
}

float CH2OSensor::getConcentration()
{
  sendData(getConcCommand);
  if (_res != NULL && checkSum())
  {
    float conc = 0;
    unsigned int temp = _res[2];
    temp *= 256;
    temp += _res[3];
    conc = temp;
    return temp;
  }
  return -255;
}
