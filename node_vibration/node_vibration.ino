#include <SoftwareSerialXT.h>
#include <SimplePacket.h>

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
const byte vibe_pin = 0;

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
  TinySerial.begin(4800);
  ET.init(&TinySerial, sizeof(myData));

  pinMode(vibe_pin, OUTPUT);
  default_flag = 1;
}

void loop()
{
  if (default_flag) {
    myData.command = 8;
    runCommand();
  }

  if (ET.receive((byte *)&myData, sizeof(myData)) && NODE_ID == myData.node_ID) {

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
        analogWrite(vibe_pin, 0);
        break;
      }
    case 1: 
      {
        analogWrite(vibe_pin, 36);
        break;
      }
    case 2:
      {
        analogWrite(vibe_pin, 72); 
        break;
      }
    case 3:
      {
        analogWrite(vibe_pin, 108);
        break;
      }
    case 4:
      {
        analogWrite(vibe_pin, 144);
        break;
      }
    case 5:
      {
        analogWrite(vibe_pin, 180);
        break;
      }
    case 6:
      {
        analogWrite(vibe_pin, 216);
        break;
      }
    case 7: 
      {
        analogWrite(vibe_pin, 255);
        break;
      }
    case 8:
      {
        for (int i = 0; i < 255; i += 1) {
          analogWrite(vibe_pin, i);
          delay(30);
        }
        break;
      }
    default:
      break;

  }
}
