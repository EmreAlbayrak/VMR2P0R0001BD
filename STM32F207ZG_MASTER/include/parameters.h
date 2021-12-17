#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <Arduino.h>
#include <EEPROM.h>

//--------------------------------------------------------------------- Motor control parameters

const uint8_t number_of_joints = 2;
const uint8_t number_of_set_parameters = 9;
const uint8_t number_of_calculated_parameters = 2;
const uint8_t number_of_storage_type = 3; // "1" for parameter values, "2" for parameter addresses.
int set_parameters_matrix [number_of_joints] [number_of_set_parameters] [number_of_storage_type];
int calculated_parameters_matrix[number_of_joints][number_of_calculated_parameters];

//--------------------------------------------------------------------- EEPROM Addresses

uint8_t address_thread_distance_1 = 0;
uint8_t address_thread_distance_2 = 2;
uint8_t address_pulley_perimeter_1 = 4;
uint8_t address_pulley_perimeter_2 = 8;
uint8_t address_motor_fullcycle_step_1 = 12;
uint8_t address_motor_fullcycle_step_2 = 14;
uint8_t address_microstep_coeff_1 = 16;
uint8_t address_microstep_coeff_2 = 17;
uint8_t address_input_speed_steady_1 = 18;
uint8_t address_input_speed_steady_2 = 20;
uint8_t address_input_acceleration_1 = 22;
uint8_t address_input_acceleration_2 = 23;
uint8_t address_driving_mechanism = 24;
uint8_t address_step_time_speed_min_1 = 26;
uint8_t address_step_time_speed_min_2 = 30;


//--------------------------------------------------------------------- Constant parameters

const char compile_date[] = __DATE__ " " __TIME__;

//TODO: Define EEPROM Addresses in the "parameter_matrix"


#endif