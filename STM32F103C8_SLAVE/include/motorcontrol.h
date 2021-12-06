#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>

void motor_power_on(uint32_t);

void motor_power_off(uint32_t);

void motor_direction_of_rotation(char, uint32_t);

uint32_t acceleration_control(uint32_t, uint32_t);

void parse_distance(String motion_type);

void drive_motor(uint32_t system_cycle_linear_coeff, uint32_t step, uint32_t step_time_speed_min, uint32_t step_time_speed_steady, uint32_t step_count_acceleration, uint32_t pulse_pin);

void start_motion(String package_income);

#endif

