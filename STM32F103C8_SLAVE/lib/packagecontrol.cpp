#include "packagecontrol.h"
#include <Arduino.h>

void package_address_control(){

}

boolean package_length_control(String package, uint8_t expected_package_length){
    uint8_t length_of_package = package.length(); 
    if(length_of_package = expected_package_length){
        return true;
    }
    else{
        return false;
    }
}

void set_parameters(uint8_t parameter_ID, uint32_t parameter_value){
    switch(parameter_ID){
        case 1:
            input_step_time_speed_steady = parameter_value;
            break;
        case 2:
            input_step_time_speed_min = parameter_value;
            break;
        case 3:
            input_step_count_acceleration = parameter_value;
        case 4:
            input_microstep_coeff = parameter_value;
        default:
            //send_error_feedback() TODO: Arrange feedback packaegs

    }
}

void send_error_feedback(uint8_t feedback_ID){

}

void send_confirm_feedback(uint8_t feedback_ID){

}