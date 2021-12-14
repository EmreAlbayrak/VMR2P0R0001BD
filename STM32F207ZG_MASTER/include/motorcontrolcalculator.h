#ifndef MOTORCONTROLCALCULATOR_H
#define MOTORCONTROLCALCULATOR_H
#include <Arduino.h>

void speed_acceleration_calculator_leadscrew(uint32_t input_step_time_speed_min, uint8_t microstep_coeff, uint32_t thread_distance, uint16_t input_speed_steady, uint16_t motor_fullcycle_step, uint16_t input_acceleration);
void speed_acceleration_calculator_pulley(uint32_t input_step_time_speed_min, uint8_t microstep_coeff, uint32_t pulley_diameter, uint16_t input_speed_steady, uint16_t motor_fullcycle_step, uint16_t input_acceleration);
void move_motor(uint8_t slave_ID, char direction_of_rotation, uint32_t steps);
#endif 