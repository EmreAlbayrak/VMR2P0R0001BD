#include <Arduino.h>
#include <EEPROM.h>
#include "defines.h"
#include "packagecontrol.h"
#include "motorcontrolcalculator.h"

EthernetUDP Udp;

void package_analyser(String package_input){
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  char command_type = package_input[1];
  uint8_t slave_ID = package_input.substring(2,3).toInt();
  if(package_format_controller(package_input, 11)){
    switch (command_type) {
      case 'S': {
        uint8_t parameter_ID = package_input.substring(3,5).toInt();
        uint32_t parameter_value = package_input.substring(5,12).toInt();
        set_parameters(slave_ID, parameter_ID, parameter_value);
        break;
      }
      case 'M': {
        uint32_t steps = package_input.substring(5,11).toInt();
        char direction_of_rotation = package_input[4]; 
        move_motor(slave_ID, direction_of_rotation, steps);
        break;
      }
      case 'G': {
        get_parameters();
        break;
      }
    }
  }
}
void setup() { //TODO: Fill the parameters EEPROM address matrix in here or in parameters.h
  Serial.begin(115200);
  uint16_t index = millis() % NUMBER_OF_MAC;
  char16_t package_buffer[255]; // buffer to hold incoming packet
  Ethernet.begin(mac[index], ip); // Use Static IP
  Udp.begin(localPort);
  get_parameters();
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