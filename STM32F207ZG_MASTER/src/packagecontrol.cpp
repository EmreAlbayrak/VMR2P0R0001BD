#include <packagecontrol.h>
#include <Arduino.h>

bool package_size_and_format_controller(String package, uint8_t package_length){
    uint32_t package_length_calculated = package.length();
    if(package_length_calculated = package_length && package[0] == '>'){
        return true;
    }
}

void set_parameters(String slave_ID, String parameter_ID, uint32_t parameter_value){
}
void move_motor(String slave_ID, uint32_t steps){
}