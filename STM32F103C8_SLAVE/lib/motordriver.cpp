#include "motordriver.h"
//#include <Arduino.h>

void motor_power_on(uint32_t enable_pin){
    digitalWrite(enable_pin, HIGH);
}

void motor_power_off(uint32_t enable_pin){
    digitalWrite(enable_pin, LOW);
}

void set_direction_of_rotation_positive(uint32_t direction_pin){
    digitalWrite(direction_pin, HIGH);
}

void set_direction_of_rotation_negative(uint32_t direction_pin){
    digitalWrite(direction_pin, LOW);
}

uint32_t acceleration_control(uint32_t step_count_acceleration_calculated,uint32_t step){
    if(step / 2 > step_count_acceleration_calculated){
        return step_count_acceleration_calculated;
    }
    else{
        return step / 2;
    }
}

void move_motor(uint32_t system_cycle_linear_coeff,uint32_t step,uint32_t step_time_speed_min,uint32_t step_time_speed_steady,uint32_t step_count_acceleration,uint32_t pulse_pin){
//--------------------------------------------------------------------- Driving motor
    uint32_t step_time_speed_instantaneous;
    for(int step_counter = 0 ; step_counter < step ; step_counter++){
        digitalWrite(pulse_pin, HIGH);
        delayMicroseconds(step_time_speed_instantaneous);
        digitalWrite(pulse_pin, LOW);
        delayMicroseconds(step_time_speed_instantaneous);
//---------------------------------------------------------------------- Applying acceleration (Changing speed each cycle)
        if(step_counter < step_count_acceleration){
        step_time_speed_instantaneous = map(step_counter, 0, step_count_acceleration, step_time_speed_min, step_time_speed_steady);
        }
        else if(step_counter > step - step_count_acceleration){
        step_time_speed_instantaneous = map(step_counter, step - step_count_acceleration, step, step_time_speed_steady, step_time_speed_min);
        }
    }
}