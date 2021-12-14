#include "packagecontrol.h"
#include "parameters.h"
#include <Arduino.h>
#include <EEPROM.h>

bool package_format_controller(String package, uint8_t package_length){
    uint32_t package_length_calculated = package.length();
    if(package_length_calculated = package_length && package[0] == '>'){
        return true;
    }
    return false;
}
void set_parameters(uint8_t slave_ID, uint8_t parameter_ID, uint32_t parameter_value){
    parameters_matrix[slave_ID][parameter_ID][1] = parameter_value;
    EEPROM.write(parameters_matrix[slave_ID][parameter_ID][2], parameters_matrix[slave_ID][parameter_ID][1]);
}
void get_parameters(){
    Serial.println("---------------------------------------------------------Service Info Start\n");
    Serial.println("Compile Date: ");
    Serial.print(compile_date);    
    for(int joint_number = 0; joint_number < number_of_joints; joint_number++){
        for(int parameter_number = 0; parameter_number < number_of_parameters; parameter_number++){
            uint8_t parameter = EEPROM.read(parameters_matrix[joint_number][parameter_number][2]);
            parameters_matrix[joint_number][parameter_number][1] = parameter;
            String serial_package = "Joint ID: " + String(joint_number) + " / Parameter ID: " + String(parameter_number) + " / Parameter Value: " + String(parameter);
        }
    }
    Serial.println("---------------------------------------------------------Service Info End\n"); 
}
