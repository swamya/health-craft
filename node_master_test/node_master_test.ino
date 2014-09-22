#include <SoftwareSerialXT.h>
#include <SimplePacket.h>

SoftwareSerialXT mySerial(3, 4, false); //receive, transmit, inverse_logic
SimplePacket ET; 

struct SEND_DATA_STRUCTURE{
  uint8_t node_ID;
  uint8_t command;
};

SEND_DATA_STRUCTURE myData;

void setup(){
  mySerial.begin(4800);
  ET.init(&mySerial, sizeof(myData));
  Serial.begin(9600);
}

void loop(){
  while (Serial.available() > 0) {
    // Format Node ID, Command
    int id = Serial.parseInt(); 
    int command = Serial.parseInt(); 
    
    if (Serial.read() == '\n') {
      Serial.print("Node: ");
      Serial.print(id);
      Serial.print(" Command:");
      Serial.println(command);
      myData.node_ID = id;
      myData.command = command;
      ET.send((byte *)&myData, sizeof(myData));
      delay(500);
    }
  }
}

