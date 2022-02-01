#include <Arduino.h>
#include "parameters.h"
#include "motorcontrol.h"
#include "packagecontrol.h"

void command_control(String package_income){
  char command_type = package_income.charAt(2);
  if(package_length_control(package_income, length_of_package_income) == 'T'){
    switch (command_type){
      case 'C': { //IO Control
        char output_ID = package_income.charAt(3);
        uint8_t value = package_income.substring(4,5).toInt();
        switch(output_ID){
          case 'M':
            send_confirm_feedback(slave_ID, "C", "00");
            digitalWrite(motor_enable_pin, value);
            break;
          default:
            send_error_feedback(slave_ID, "P", "05");
            break;
        }
        break;
      }
      case 'S': { //Set Parameters
        uint8_t parameter_ID = package_income.substring(3,5).toInt();
        uint32_t parameter_value = package_income.substring(5,11).toInt();
        switch(parameter_ID){
          case 1:
            input_step_time_speed_steady = parameter_value;
            send_confirm_feedback(slave_ID, "S", package_income.substring(3,5));
            break;
          case 2: 
            input_step_time_speed_min = parameter_value;
            send_confirm_feedback(slave_ID, "S", package_income.substring(3,5));
            break;
          case 3: 
            input_step_count_acceleration = parameter_value;
            send_confirm_feedback(slave_ID, "S", package_income.substring(3,5));
            break;
          case 4: 
            input_microstep_coeff = parameter_value;
            send_confirm_feedback(slave_ID, "S", package_income.substring(3,5));
            break;
          default: 
            send_error_feedback(slave_ID, "P", "04");
        }
        break;
      }
      case 'M': { //Motor Move
        send_confirm_feedback(slave_ID, "M", "01"); 
        uint32_t input_step = package_income.substring(4,11).toInt(); 
        step_count_acceleration = motor_acceleration_control(input_step_count_acceleration, input_step);
        motor_direction_of_rotation(package_income[4], motor_direction_pin);
        motor_drive(input_step, input_step_time_speed_min, input_step_time_speed_steady, input_step_count_acceleration, motor_pulse_pin);
        send_confirm_feedback(slave_ID, "A", "01"); 
        break;
      }
      case 'G': { //Get Feedback
        send_confirm_feedback(slave_ID, "G", "01");
        Serial.print("Compile Date: ");
        Serial.println(compile_date);

        break;
      }
      case 'H': {
        send_confirm_feedback(slave_ID, "H", "01");
        motor_power_on(motor_enable_pin);
        motor_drive_home(sensor_limit_switch_pin, input_step_time_speed_min, input_step_time_speed_steady, motor_pulse_pin);
        send_confirm_feedback(slave_ID, "A", "01");
        motor_power_off(motor_enable_pin);
        break;
      }
      default: { //Send Error
        send_error_feedback(slave_ID, "P", "02");
        break;
      }
    }
  }
  else{
    send_error_feedback(slave_ID, "P", "01");
  }
}
void setup() { 
  Serial.begin(115200);
//--------------------------------------- State here the relevent IO's decleration
  pinMode(motor_pulse_pin, OUTPUT);
  pinMode(motor_direction_pin, OUTPUT);
  pinMode(motor_enable_pin, OUTPUT);

  motor_power_on(motor_enable_pin);
}
void loop() {
  if(Serial.available()>0){
    String package_income = Serial.readString();
    Serial.println(package_income);
    command_control(package_income);
  }
}