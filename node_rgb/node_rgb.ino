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
const byte red_pin = 1;
const byte green_pin = 4;
const byte blue_pin = 0;

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

  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  
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
        setRGB(0,0,0);
        break;
      }
    case 1: //red
      {
        setRGB(255,0,0);
        break;
      }
    case 2:
      {
        setRGB(255,85,0);
        break;
      }
    case 3:
      {
        setRGB(255,170,0);
        break;
      }
    case 4: //yellow
      {
        setRGB(255,255,0);
        break;
      }
    case 5:
      {
        setRGB(170,255,0);
        break;
      }
    case 6:
      {
        setRGB(85,255,0);
        break;
      }
    case 7: //green
      {
        setRGB(0, 255, 0);
        break;
      }
    case 8:
      {
        byte red = 255;
        byte green = 0;
        byte blue = 0;
        
        setRGB(red,green,blue);
        delay(30);
        
        for (byte i = 0; i < 255; i++){ //red to yellow
           green += 1;
           setRGB(red, green, blue);
           delay(30); 
        }
        for (byte i = 0; i < 255; i++){ //yellow to green
           red -= 1;
           setRGB(red, green, blue);
           delay(30); 
        }
        
        delay(30);
        
        for (byte i = 0; i < 255; i++){ //green  to yellow
           red += 1;
           setRGB(red, green, blue);
           delay(30); 
        }
        for (byte i = 0; i < 255; i++){ //yellow to red
           green -= 1;
           setRGB(red, green, blue);
           delay(30); 
        }
        
        break;
      }
    default:
      break;

  }
}
void setRGB(byte red, byte green, byte blue){
   analogWrite(red_pin, red);
   analogWrite(green_pin, green);
   analogWrite(blue_pin, blue);
}
