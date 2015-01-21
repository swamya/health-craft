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

const byte NODE_ID = 4;
SoftwareSerialXT TinySerial(2);
SimplePacket ET;
const byte buzzer_pin = 0;

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

  pinMode(buzzer_pin, OUTPUT);
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
        digitalWrite(buzzer_pin, LOW);
        break;
      }
    case 1:
      {
        birdSound();
        delay(10000);
        break;
      }
    case 2:
      {
        for (int i = 0; i < 2; i++){
          birdSound();
          delay(2000); 
        }
        delay(10000);
        break;
      }
    case 3:
      {
        for (int i = 0; i < 3; i++) {
          birdSound();
          delay(2000);
        }
        delay(10000);
        break;
      }
    case 4:
      {
        for (int i = 0; i < 4; i++) {
          birdSound();
          delay(2000);
        }
        delay(10000);
        break;
      }
    case 5:
      {
        for (int i = 0; i < 5; i++) {
          birdSound();
          delay(2000);
        }
        delay(10000);
        break;
      }
    case 6:
      {
        for (int i = 0; i < 6; i++) {
          birdSound();
          delay(2000);
        }
        delay(10000);
        break;
      }
    case 7:
      {
        for (int i = 0; i < 7; i++) {
          birdSound();
          delay(2000);
        }
        delay(10000);
        break;
      }
    case 8:
      {
        birdSound();
        delay(3000);
        break;
      }
    default:
      break;

  }
}
void birdSound() {
  int val = random(2, 20);
  //makes the sound according to: intensity, varies: normally 5. number of times: how many times tweets, rormally 3-6
  highChirp(5, val / 10);
  lowChirp(val * 4, 2);
  tweet(0, 2);
  tweet(0, 4);
  lowChirp(val * 8, 2);
  highChirp(5, val / 5);
  highChirp(5, val / 5);
  highChirp(2, val / 2);
  lowChirp(val * 8, 2);
  tweet(0, 4);
  tweet(0, 4);
  lowChirp(val * 8, 2);
}

void tweet(int intensity, int chirpsNumber) {

  //normal chirpsNumber 3, normal intensity 5

  for (int veces = 0; veces < chirpsNumber; veces++) {

    for (int i = 80; i > 0; i--)
    {
      for  (int x = 0; x < intensity;  x++)
      {
        digitalWrite (buzzer_pin, HIGH);
        digitalWrite (buzzer_pin, LOW);
      }
    }
  }
}


void highChirp(int intensity, int chirpsNumber) {
  int i;
  int x;

  for (int veces = 0; veces <= chirpsNumber; veces++) {

    for (i = 100; i > 0; i--)
    {
      for  (x = 0; x < intensity;  x++)
      {
        digitalWrite (buzzer_pin, HIGH);
        delayMicroseconds (i);
        digitalWrite (buzzer_pin, LOW);
        delayMicroseconds (i);
      }
    }
  }
}

void lowChirp(int intensity, int chirpsNumber) {
  int i;
  int x;

  for (int veces = 0; veces <= chirpsNumber; veces++) {

    for (i = 0; i < 200; i++)
    {
      digitalWrite (buzzer_pin, HIGH);
      delayMicroseconds(i);
      digitalWrite(buzzer_pin, LOW);
      delayMicroseconds(i);
    }

    for (i = 90; i > 80; i--)
    {
      for  ( x = 0; x < 5;  x++)
      {
        digitalWrite (buzzer_pin, HIGH);
        delayMicroseconds (i);
        digitalWrite (buzzer_pin, LOW);
        delayMicroseconds (i);
      }
    }
  }
}

