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

const uint32_t motor_pulse_pin = PB13;
const uint32_t motor_direction_pin = PB14;
const uint32_t motor_enable_pin = PB15;

uint32_t limit_switch_pin = PB12; 

//--------------------------------------------------------------------- Calculated Parameters

uint32_t step_count_acceleration;

//---------------------------------------------------------------------  Constant Parameters

const uint8_t slave_ID = 1;

#endif //PARAMETERS_H