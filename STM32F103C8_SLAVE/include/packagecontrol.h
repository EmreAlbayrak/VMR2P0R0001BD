#ifndef PACKAGEANALYZER_H
#define PACKAGEANALYZER_H
#include <Arduino.h>

char package_length_control(String package, uint8_t expected_package_length);
void set_parameter(uint8_t parameter_ID, uint32_t parameter_value);
void send_confirm_feedback(String slave_ID, String confirm_type, String feedback_ID);
void send_error_feedback(String slave_ID, String error_type, String feedback_ID);
void print_parameters(String parameter_name, String parameter_value);

#endif