#ifndef PACKAGECONTROL_H
#define PACKAGECONTROL_H

#include <Arduino.h>

bool package_size_and_format_controller(String package, uint8_t package_length);
void set_parameters(String slave_ID, String parameter_ID, uint32_t parameter_value);
void move_motor(String slave_ID, uint32_t steps);

#endif 