#include <Arduino.h>
#include "parameters.h"
#include "motorcontrol.h"
#include "packagecontrol.h"

const char compile_date[] = __DATE__ " " __TIME__; 

void command_control(String package_income){
    char command_type = package_income.charAt(2); 
    switch(command_type){

      case 'S':
          set_parameters(package_income);
          break;

      case 'M':
          motor_power_on(motor_enable_pin);
          motor_direction_of_rotation(package_income[4], motor_direction_pin);
          
          drive_motor(input_system_cycle_linear_coeff, input_step, input_step_time_speed_min, input_step_time_speed_steady, input_step_count_acceleration, motor_pulse_pin);
          break;
      case 'G':
          break;
      default:
          send_feedback(1);
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