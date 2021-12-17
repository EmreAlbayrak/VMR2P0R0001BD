#ifndef PACKAGECONTROL_H
#define PACKAGECONTROL_H

#include <Arduino.h>

bool package_format_controller(String package, uint8_t package_length);
void sync_parameter(uint8_t parameter_ID, uint32_t parameter_value);
#endif 