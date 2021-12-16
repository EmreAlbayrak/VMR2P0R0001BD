#include "motorcontrolcalculator.h"
#include <Arduino.h>

float_t pi = 3.141592;

uint16_t acceleration_calculator_leadscrew(uint32_t step_time_speed_steady, uint32_t step_time_speed_min, uint8_t microstep_coeff, uint32_t thread_distance, uint16_t input_speed_steady, uint16_t motor_fullcycle_step, uint16_t input_acceleration){
  float delta_t = input_speed_steady / input_acceleration; // Delta time that acceleration going to be applied on x-axis
  uint32_t step_time_acceleration_avg = (step_time_speed_min - step_time_speed_steady) / 2; // Assuming acceleration is 0 and speed is constant at step_time_speed_steady_x/2 on x-axis
  uint16_t step_count_acceleration_calculated = delta_t*pow(10, 6) / (step_time_acceleration_avg * 2); //Number of steps that acceleration going to be applied on x-axis (2 delay for one step)
  return step_count_acceleration_calculated;
}
uint32_t speed_calculator_leadscrew(uint32_t step_time_speed_min, uint8_t microstep_coeff, uint32_t thread_distance, uint16_t input_speed_steady, uint16_t motor_fullcycle_step){
  uint32_t step_time_speed_steady = thread_distance*pow(10, 6) / (input_speed_steady*motor_fullcycle_step*microstep_coeff*2);
  return step_time_speed_steady;
}
uint16_t acceleration_calculator_pulley(uint32_t step_time_speed_steady, uint32_t step_time_speed_min, uint8_t microstep_coeff, uint32_t pulley_diameter, uint16_t input_speed_steady, uint16_t motor_fullcycle_step, uint16_t input_acceleration){
  float delta_t = input_speed_steady / input_acceleration; // Delta time that acceleration going to be applied on x-axis
  uint32_t step_time_acceleration_avg = ((step_time_speed_min / microstep_coeff) - step_time_speed_steady) / 2; // Assuming acceleration is 0 and speed is constant at step_time_speed_steady_x/2 on x-axis
  uint16_t step_count_acceleration_calculated = round((delta_t * pow(10, 6)) / (step_time_acceleration_avg * 2)); //Number of steps that acceleration going to be apply on x-axis (2 delay for one step)
  Serial.print("Service Info: step_count_acceleration_calculated = ");
  Serial.println(step_count_acceleration_calculated);
  return step_count_acceleration_calculated;
}

uint32_t speed_calculator_pulley(uint32_t step_time_speed_min, uint8_t microstep_coeff, uint32_t pulley_diameter, uint16_t input_speed_steady, uint16_t motor_fullcycle_step){
  uint32_t step_time_speed_steady = round((pi*pulley_diameter*pow(10, 6)) / (input_speed_steady * motor_fullcycle_step * microstep_coeff * 2));
  Serial.print("Service Info: step_time_speed_steady = ");
  Serial.println(step_time_speed_steady);
  return step_time_speed_steady;
}

void move_motor(uint8_t slave_ID, char direction_of_rotation, uint32_t steps){
    String serial_slave_command = ">" + String(slave_ID) + "M" + direction_of_rotation + String(steps);
}