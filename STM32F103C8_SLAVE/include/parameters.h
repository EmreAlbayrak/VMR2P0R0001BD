#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <Arduino.h>

//--------------------------------------------------------------------- Input Parameters 

//uint32_t input_step;
uint32_t input_step_time_speed_steady;
uint32_t input_step_time_speed_min;
uint32_t input_step_count_acceleration;
uint32_t input_microstep_coeff;
uint32_t input_system_cycle_linear_coeff;

//--------------------------------------------------------------------- Hardware Connection Parameters

const uint8_t motor_pulse_pin = PA1;//PB13
const uint8_t motor_direction_pin = PC15;//PB14
const uint8_t motor_enable_pin = PC13; //TODO: Change after test to PB15
const uint8_t sensor_limit_switch_pin = PC14; //PB12 

//--------------------------------------------------------------------- Calculated Parameters

uint32_t step_count_acceleration;

//---------------------------------------------------------------------  Constant Parameters

const String slave_ID = "1";

const uint8_t length_of_package_income = 11;

const char compile_date[] = __DATE__ " " __TIME__; 

#endif //PARAMETERS_H