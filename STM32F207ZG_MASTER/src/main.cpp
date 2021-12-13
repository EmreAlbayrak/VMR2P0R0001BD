#include <Arduino.h>
#include <EEPROM.h>
#include "defines.h"
#include "parameters.h"
#include "packagecontrol.h"

EthernetUDP Udp;

void package_analyser(String package_input){
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  char command_type = package_input[1];
  if(package_size_controller(package_input, 12)){
    switch (command_type) {
      
           
    }
  }
}
void setup() {
  Serial.begin(115200);
  uint16_t index = millis() % NUMBER_OF_MAC;
  char16_t package_buffer[255]; // buffer to hold incoming packet
  Ethernet.begin(mac[index], ip); // Use Static IP
  Udp.begin(localPort);
}
void loop() {
    int package_size = Udp.parsePacket();
    if(package_size){
      int len = Udp.read(package_buffer, 255);
      if(len>0){
        package_buffer[len] = 0;
      }
      package_analyser(package_buffer);
    }
    if(Serial.available() > 0){
      String serial_package = Serial.readString();
      package_analyser(serial_package);
    }
}