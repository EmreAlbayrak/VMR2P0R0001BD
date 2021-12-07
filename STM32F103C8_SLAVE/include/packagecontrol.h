#ifndef PACKAGEANALYZER_H
#define PACKAGEANALYZER_H

#include "parameters.h"

boolean package_length_control(String package, uint8_t expected_package_length);
void set_parameter(uint8_t parameter_ID, uint32_t parameter_value);
void send_confirm_feedback(uint8_t feedback_ID);
void send_error_feedback(uint8_t feedback_ID);

#endif