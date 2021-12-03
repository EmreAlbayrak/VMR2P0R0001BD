#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include <Arduino.h>

void motor_power_on(uint32_t);

void motor_power_off(uint32_t);

void set_direction_of_rotation_positive(uint32_t);

void set_direction_of_rotation_negative(uint32_t);

uint32_t acceleration_control(uint32_t, uint32_t);

void move_motor(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

#endif //MOTORDRIVER

