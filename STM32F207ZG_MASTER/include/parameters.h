#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <Arduino.h>

String serial_package; //Incoming package from serial,

//--------------------------------------------------------------------- Motor control parameters
const uint8_t number_of_joints = 2;
const uint8_t number_of_parameters = 8;
const uint8_t storage_type = 2; // "1" for parameter values, "2" for parameter addresses.
int parameters_matrix [number_of_joints] [number_of_parameters] [storage_type];
uint16_t thread_distance = 10; // In units of millimeter
float_t pulley_diameter = 37.5; //In units of millimeter
uint16_t motor_fullcycle_step = 400; // Motor's full cycle number of steps
uint8_t microstep_coeff = 2; // Motor driver's microstep setting
uint16_t max_speed = 150; // In units of mm/s
uint32_t step_time_speed_steady = 0; // In units of microsecond
uint32_t step_time_speed_min = 8000; // In units of microsecond
uint32_t step_time_instantaneous = 0; // In units of microsecond
uint32_t step_time_acceleration_avg = 0; // In units of microsecond
uint32_t step_count_acceleration = 0; // Number of steps that acceleration going to applied on x-axis
uint32_t step_time_speed_home = 1400; 
uint16_t input_speed_steady = 0; // In units of mm/s
uint8_t input_acceleration = 0; // In units of mm/(s^2)
char16_t driving_mechanism = '0'; // "0" -> Pulley System, "1" -> Lead Screw 
float_t delta_t = 0; // Time that acceleration is going to apply on x-axis
uint32_t step_count_acceleration_calculated = 0; //Memory for step_count_acceleration_x calculation 
float_t system_cycle_linear_distance = 0; // The varible keeps linear distance of one cycle for x-axis
float_t degree;
uint32_t step;

//--------------------------------------------------------------------- EEPROM Addresses

uint8_t address_thread_distance_1 = 0;
uint8_t address_thread_distance_2 = 2;
uint8_t address_pulley_diameter_1 = 4;
uint8_t address_pulley_diameter_2 = 8;
uint8_t address_motor_fullcycle_step_1 = 12;
uint8_t address_motor_fullcycle_step_2 = 14;
uint8_t address_microstep_coeff_1 = 16;
uint8_t address_microstep_coeff_2 = 17;
uint8_t address_input_speed_steady_1 = 18;
uint8_t address_input_speed_steady_2 = 20;
uint8_t address_input_acceleration_1 = 22;
uint8_t address_input_acceleration_2 = 23;
uint8_t address_driving_mechanism = 24;
uint8_t address_step_delay_speed_min_1 = 26;
uint8_t address_step_delay_speed_min_2 = 30;


//--------------------------------------------------------------------- Constant parameters

const char compile_date[] = __DATE__ " " __TIME__;

#endif PARAMETERS_H
