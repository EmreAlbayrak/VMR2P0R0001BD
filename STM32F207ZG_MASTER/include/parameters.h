#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <Arduino.h>

String serial_package; //Incoming package from serial,

//--------------------------------------------------------------------- Motor control parameters

uint16_t thread_distance_x = 10; // In units of millimeter
uint16_t thread_distance_y = 10; // In units of millimeter
float_t pulley_diameter_x = 37.5; //In units of millimeter
float_t pulley_diameter_y = 37.5; //In units of millimeter
uint16_t motor_fullcycle_step_x = 400; // Motor's full cycle number of steps
uint16_t motor_fullcycle_step_y = 400; // Motor's full cycle number of steps
uint8_t microstep_coeff_x = 2; // Motor driver's microstep setting
uint8_t microstep_coeff_y = 2; // Motor driver's microstep setting
uint16_t max_speed_x = 150; // In units of mm/s
uint16_t max_speed_y = 150; // In Units of mm/s
uint32_t step_delay_speed_steady_x = 0; // In units of microsecond
uint32_t step_delay_speed_steady_y = 0; // In units of microsecond
uint32_t step_delay_speed_min_x = 8000; // In units of microsecond
uint32_t step_delay_speed_min_y = 8000; // In units of microsecond
uint32_t step_delay_instantaneous_x = 0; // In units of microsecond
uint32_t step_delay_instantaneous_y = 0; // In units of microsecond
uint32_t step_delay_acceleration_avg_x = 0; // In units of microsecond
uint32_t step_delay_acceleration_avg_y = 0; // In units of microsecond
uint32_t step_count_acceleration_x = 0; // Number of steps that acceleration going to applied on x-axis
uint32_t step_count_acceleration_y = 0; // Number of steps that acceleration going to applied on y-axis
uint32_t step_delay_speed_home_x = 1400; 
uint32_t step_delay_speed_home_y = 1400;
uint16_t input_speed_steady_x = 0; // In units of mm/s
uint16_t input_speed_steady_y = 0; // In units of mm/s
uint8_t input_acceleration_x = 0; // In units of mm/(s^2)
uint8_t input_acceleration_y = 0; // In units of mm/(s^2)
char16_t driving_mechanism = '0'; // "0" -> Pulley System, "1" -> Lead Screw 
float_t delta_t_x = 0; // Time that acceleration is going to apply on x-axis
float_t delta_t_y = 0; // Time that acceleration is going to apply on y-axis
uint32_t step_count_acceleration_calculated_x = 0; //Memory for step_count_acceleration_x calculation 
uint32_t step_count_acceleration_calculated_y = 0; //Memory for step_count_acceleration_y calculation
float_t system_cycle_linear_distance_x = 0; // The varible keeps linear distance of one cycle for x-axis
float_t system_cycle_linear_distance_y = 0; // The varible keeps linear distance of one cycle for y-axis
float_t pi = 3.141592; //pi number
float_t degree_x;
float_t degree_y;
uint32_t step_x;
uint32_t step_y;

//--------------------------------------------------------------------- EEPROM Addresses

uint8_t address_thread_distance_x = 0;
uint8_t address_thread_distance_y = 2;
uint8_t address_pulley_diameter_x = 4;
uint8_t address_pulley_diameter_y = 8;
uint8_t address_motor_fullcycle_step_x = 12;
uint8_t address_motor_fullcycle_step_y = 14;
uint8_t address_microstep_coeff_x = 16;
uint8_t address_microstep_coeff_y = 17;
uint8_t address_input_speed_steady_x = 18;
uint8_t address_input_speed_steady_y = 20;
uint8_t address_input_acceleration_x = 22;
uint8_t address_input_acceleration_y = 23;
uint8_t address_driving_mechanism = 24;
uint8_t address_step_delay_speed_min_x = 26;
uint8_t address_step_delay_speed_min_y = 30;


//--------------------------------------------------------------------- Constant parameters

const char compile_date[] = __DATE__ " " __TIME__;

#endif PARAMETERS_H
