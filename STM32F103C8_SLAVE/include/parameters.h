#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <Arduino.h>

//--------------------------------------------------------------------- Input Parameters 

uint32_t input_step;
uint32_t input_step_time_speed_steady;
uint32_t input_step_time_speed_min;
uint32_t input_step_count_acceleration;
uint32_t input_microstep_coeff;
uint32_t input_system_cycle_linear_coeff;

//--------------------------------------------------------------------- Hardware Connection Parameters

uint32_t motor_pulse_pin = A6;
uint32_t motor_direction_pin = A5;
uint32_t motor_enable_pin = A4;

//--------------------------------------------------------------------- Calculated Parameters
uint32_t step_count_acceleration;

#endif //PARAMETERS_H