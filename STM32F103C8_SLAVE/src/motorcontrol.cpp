#include "motorcontrol.h"
#include <Arduino.h>

void motor_power_on(uint8_t enable_pin){
    digitalWrite(enable_pin, HIGH);
}
void motor_power_off(uint8_t enable_pin){
    digitalWrite(enable_pin, LOW);
}
void motor_direction_of_rotation(char direction, uint8_t direction_pin){

    if(direction == 'P'){
        digitalWrite(direction_pin, HIGH);
    }
    else if(direction == 'N'){
        digitalWrite(direction_pin, LOW);
    }
    else{
        //TODO: Send Required Feedback
    }
}
uint32_t motor_acceleration_control(uint32_t step_count_acceleration_calculated, uint32_t step){

    if(step / 2 > step_count_acceleration_calculated){
        return step_count_acceleration_calculated;
    }
    else{
        return step / 2;
    }
}
void motor_drive(uint32_t step, uint32_t step_time_speed_min, uint32_t step_time_speed_steady, uint32_t step_count_acceleration, uint32_t pulse_pin){
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
void motor_drive_home(uint8_t sensor_limit_switch_pin, uint32_t step_time_speed_min, uint32_t step_time_speed_steady, uint8_t pulse_pin){
    bool limit_switch_flag = true;
    bool toggle = true;
    unsigned long time = 0;
    while(limit_switch_flag){
        if(digitalRead(sensor_limit_switch_pin) == HIGH){
            if(toggle == true){
                time = millis();
                toggle = false;
            }
            if(millis() - time >= 1){
                limit_switch_flag == false;
            }
        }
        else{
            toggle = true;
        }
        digitalWrite(pulse_pin, HIGH);
        delayMicroseconds(step_time_speed_steady);
        digitalWrite(pulse_pin, LOW);
        delayMicroseconds(step_time_speed_steady);
    }
}