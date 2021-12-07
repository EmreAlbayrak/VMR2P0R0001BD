#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>

void motor_power_on(uint8_t enable_pin);
void motor_power_off(uint8_t enable_pin);
void motor_direction_of_rotation(char direction, uint8_t direction_pin);
uint32_t motor_acceleration_control(uint32_t step_count_acceleration_calculated, uint32_t step);
void motor_drive(uint32_t step, uint32_t step_time_speed_min, uint32_t step_time_speed_steady, uint32_t step_count_acceleration, uint32_t pulse_pin);

#endif

