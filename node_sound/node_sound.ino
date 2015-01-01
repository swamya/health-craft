#include <SoftwareSerialXT.h>
#include <SimplePacket.h>
#include <TinyWireM.h>

#define eeprom 0x50

//#define DEBUG
#ifdef DEBUG
#define DEBUG_CODE(code_fragment) { code_fragment }
#else
#define DEBUG_CODE(code_fragment)
#endif

#ifdef DEBUG
#include <TinyDebugKnockBang.h>
#endif

const byte NODE_ID = 1;
SoftwareSerialXT TinySerial(2);
SimplePacket ET;

struct RECEIVE_DATA_STRUCTURE {
  uint8_t node_ID;
  uint8_t command;
};

RECEIVE_DATA_STRUCTURE myData;
byte default_flag;

void setup()
{
  DEBUG_CODE(
    Debug.begin( 250000 );
  )
  TinyWireM.begin();
  TinySerial.begin(4800);
  ET.init(&TinySerial, sizeof(myData));

  default_flag = 1;
}

void loop()
{
  if (default_flag) {
    myData.command = 8;
    runCommand();
  }

  if (ET.receive((byte*)&myData, sizeof(myData)) && NODE_ID == myData.node_ID) {

    DEBUG_CODE(
      Debug.print("Node: ");
      Debug.println(myData.node_ID);
      Debug.print("Command: ");
      Debug.println(myData.command);
      Debug.println("------------");
    )
    default_flag = 0;
    runCommand();
  }
}
void runCommand() {
  switch (myData.command) {
    case 0: //off
      {
        break;
      }
    case 1:
      {
        break;
      }
    case 2:
      {
        break;
      }
    case 3:
      {
        break;
      }
    case 4:
      {
        break;
      }
    case 5:
      {
        break;
      }
    case 6:
      {
        break;
      }
    case 7:
      {
        break;
      }
    case 8:
      {
        break;
      }
    default:
      break;

  }
}

byte readEEPROM(int deviceaddress, unsigned int eeaddress)
{
  byte rdata = 0xFF;
  TinyWireM.beginTransmission(deviceaddress);
  TinyWireM.send((int)(eeaddress >> 8));
  TinyWireM.send((int)(eeaddress & 0xFF));
  TinyWireM.endTransmission();
  TinyWireM.requestFrom(deviceaddress,1);
  if (TinyWireM.available())
  {
    rdata = TinyWireM.receive();
  }
  return rdata;
}

