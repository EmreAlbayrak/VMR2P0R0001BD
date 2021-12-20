#ifndef PACKAGECONTROL_H
#define PACKAGECONTROL_H

#include <Arduino.h>

bool package_format_controller(String package, uint8_t package_length);
String zero_padding_string(String command_value, uint8_t expacted_digit_number);
void push_set_joint(String slave_ID, String parameter_ID, String parameter_value);
void push_move_joint(String slave_ID, String direction_of_rotation, String command_value);
void push_IO_joint(String slave_ID, String IO_ID, String IO_value);
#endif 