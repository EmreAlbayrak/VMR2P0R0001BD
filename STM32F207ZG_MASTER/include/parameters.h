#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <Arduino.h>
#include <EEPROM.h>

//--------------------------------------------------------------------- Motor control parameters

const uint8_t number_of_joints = 2;
const uint8_t number_of_set_parameters = 9;
const uint8_t number_of_calculated_parameters = 2;
const uint8_t number_of_points = 99;
int set_parameters_matrix [number_of_joints] [number_of_set_parameters];
int set_parameters_address_matrix [number_of_joints] [number_of_set_parameters];
int calculated_parameters_matrix[number_of_joints][number_of_calculated_parameters];
int current_position_matrix[number_of_joints]; //Cartesian position matrix
int points_matrix[99][2]; // first digit stores point ID, second digit stores axis (1 -> for x-axis, 2 -> for y-axis), thir digit (1 -> holds value, 2 -> holds EEPROM address)
int points_address_matrix[99][2];

//--------------------------------------------------------------------- EEPROM Addresses 

uint8_t address_thread_distance_1 = 0;
uint8_t address_pulley_perimeter_1 = 4;
uint8_t address_motor_fullcycle_step_1 = 8;
uint8_t address_microstep_coeff_1 = 12;
uint8_t address_input_speed_steady_1 = 16;
uint8_t address_input_acceleration_1 = 20;
uint8_t address_step_time_speed_min_1 = 24;
uint8_t address_thread_distance_2 = 28;
uint8_t address_pulley_perimeter_2 = 32;
uint8_t address_motor_fullcycle_step_2 = 36;
uint8_t address_microstep_coeff_2 = 40;
uint8_t address_input_speed_steady_2 = 44;
uint8_t address_input_acceleration_2 = 48;
uint8_t address_step_time_speed_min_2 = 52;
uint8_t address_driving_mechanism = 56;

//--------------------------------------------------------------------- EEPROM Address Generator for Destination Points Storage


//--------------------------------------------------------------------- Constant parameters

const char compile_date[] = __DATE__ " " __TIME__;

//TODO: Define EEPROM Addresses in the "parameter_matrix

#endif