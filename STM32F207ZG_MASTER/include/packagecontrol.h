#ifndef PACKAGECONTROL_H
#define PACKAGECONTROL_H

#include <Arduino.h>
uint32_t string_to_uint32_converter(String string_input); //TODO: Delete after test - Not used
bool package_format_controller(String package, uint8_t package_length);
String zero_padding_string(String command_value, uint8_t expacted_digit_number);
void push_set_joint(String slave_ID, String parameter_ID, String parameter_value);
void push_move_joint(String slave_ID, String direction_of_rotation, String command_value);
void push_IO_joint(String slave_ID, String IO_ID, String IO_value);
void push_home_command(String slave_ID);
void print_feedback(String slave_ID, String feedbak_type, uint8_t feedback_ID);
#endif 