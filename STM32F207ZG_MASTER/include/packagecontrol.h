#ifndef PACKAGECONTROL_H
#define PACKAGECONTROL_H

#include <Arduino.h>

bool package_format_controller(String package, uint8_t package_length);
void set_parameters(uint8_t slave_ID, uint8_t parameter_ID, uint32_t parameter_value);
void get_parameters();
#endif 