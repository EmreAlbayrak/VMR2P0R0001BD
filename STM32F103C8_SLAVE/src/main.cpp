#include <Arduino.h>
#include "parameters.h"
#include "motorcontrol.h"
#include "packagecontrol.h"

void command_control(String package_income){
    char command_type = package_income.charAt(2);
    if(package_length_control(package_income, length_of_package_income)){
    switch (command_type){
      case 'C': {
        
      }
      case 'S': { //Set Parameters
        uint8_t parameter_ID = package_income.substring(3,5).toInt();
        uint32_t parameter_value = package_income.substring(5,11).toInt();
        set_parameter(parameter_ID, parameter_value);
        break;
      }
      case 'M': { //Motor Move
        motor_power_on(motor_enable_pin);
        motor_direction_of_rotation(package_income[4], motor_direction_pin);
        step_count_acceleration = motor_acceleration_control(input_step_count_acceleration, input_step);
        motor_drive(input_step, input_step_time_speed_min, input_step_time_speed_steady, input_step_count_acceleration, motor_pulse_pin);
        //send_confirm_feedback() //TODO: Send required confirm feedback
        break;
      }
      case 'G': { //Get Feedback
        send_confirm_feedback(5);
        break;
      }
      default: {
        send_error_feedback(1);
      }
    }
    }

    
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Compile Date: ");
  Serial.println(compile_date);
  delay(1000);
}